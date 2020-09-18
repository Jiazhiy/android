#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <pthread.h>
#include <alloca.h>
#include "atchannel.h"
#include "at_tok.h"
#include "misc.h"
#include <getopt.h>
#include <linux/sockios.h>
#include <termios.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../include/telephony/ril.h"
#include <linux/un.h>
#include <linux/poll.h>

#define LOG_NDEBUG 0
#define LOG_TAG "GPS"
#include "ql-log.h"

static int ql_gps_control[2];
static int ql_is_mc20_gps = 0;
static int ql_mc20_nmea_client = 0;
typedef struct _GPS_EVENT {
    RIL_TimedCallback callback;
    void *param;
    long expire_msec;
} GPS_EVENT;
static GPS_EVENT s_gps_events[5];

static void GPS_requestTimedCallback (RIL_TimedCallback callback, void *param,
                                const struct timeval *relativeTime) {
    if (ql_gps_control[1] > 0) {
        GPS_EVENT gps_event = {callback, param, 0};
        long now_msec;
        struct timeval tv;
        gettimeofday(&tv, (struct timezone *) NULL);
        now_msec = tv.tv_sec*1000 + tv.tv_usec/1000;
        gps_event.expire_msec = now_msec;
        if (relativeTime)
            gps_event.expire_msec += relativeTime->tv_sec * 1000 + relativeTime->tv_usec/1000;
        write(ql_gps_control[1], &gps_event, sizeof(gps_event));
    }
}
static const struct timeval TIMEVAL_1 = {1,0};

typedef struct _GPS_TLV {
   int type;
   int length;
   unsigned char data[0];
} GPS_TLV;

static int s_gps_state = 0;
static pthread_t s_gps_thread;
static pthread_t s_nmea_thread;
static pthread_t s_control_thread;
static int s_agps_check_times = 0;
static void pollXTRAStateChange (void *param) {
    if (s_gps_state && s_agps_check_times--) {
        int xtradatadurtime = 0;
        ATResponse *p_response = NULL;
        int err = at_send_command_singleline("AT+QGPSXTRADATA?", "+QGPSXTRADATA: ", &p_response);
        if (err == 0 && p_response != NULL && p_response->success == 1) {
            char *line = p_response->p_intermediates->line;
            if (at_tok_start(&line) == 0) {
                at_tok_nextint(&line, &xtradatadurtime);
            }
        }   
        at_response_free(p_response);
        if (xtradatadurtime == 0)
            GPS_requestTimedCallback (pollXTRAStateChange, NULL, &TIMEVAL_1);
    }    
}

static int s_poll_pending;
static void pollNMEAReader (void *param) {
    //LOGD("%s %d %d", __func__, s_gps_state, ql_mc20_nmea_client);
    if (s_gps_state && ql_mc20_nmea_client > 0) {
        ATResponse *p_response = NULL;
        
        int err = at_send_command_multiline("AT+QGNSSRD?", "\0", &p_response);
        if (err == 0 && p_response != NULL && p_response->success == 1) {
            ATLine *p_cur = p_response->p_intermediates;
           while (p_cur) {
                const char *line = p_cur->line;
                if (!strncmp(line, "+QGNSSRD: ", strlen("+QGNSSRD: ")))
                    line += strlen("+QGNSSRD: ");

                //LOGD("%s", line);
                if (ql_mc20_nmea_client > 0) {
                    char nmea[128];
                    int len = strlen(line);
                    if (len < (sizeof(nmea)-1)) {
                        strcpy(nmea, line);
                        nmea[len++] = '\n';
                        if (write(ql_mc20_nmea_client, nmea, len) != len)
                            LOGD("send nmea errno: %d (%s)", errno, strerror(errno));
                    }
                }
            
                p_cur = p_cur->p_next;
            }
        }
        
        at_response_free(p_response);
    } 
    
    if (s_gps_state)
        GPS_requestTimedCallback (pollNMEAReader, NULL, &TIMEVAL_1);    
    else
        s_poll_pending = 0;
}

static time_t s_last_inject_time = 0;
static int s_last_inject_uncertainty = 10;
static void *s_last_inject_xtra_data = NULL;
static int s_last_inject_xtra_length = 0;
static void onGPSStateChange (void *param)
{
    char *cmd;
    ATResponse *p_response = NULL;
    int oldState = 0xff;
    GPS_TLV *extra_gps_tlv = (GPS_TLV *)param;
    int err = 0;

    if (ql_is_mc20_gps)
        err = at_send_command_singleline("AT+QGNSSC?", "+QGNSSC: ", &p_response);
    else
        err = at_send_command_singleline("AT+QGPS?", "+QGPS: ", &p_response);

    if (err == 0 && p_response != NULL && p_response->success == 1) {
        char *line = p_response->p_intermediates->line;
        if (at_tok_start(&line) == 0) {
            at_tok_nextint(&line, &oldState);
        }
    }   
    at_response_free(p_response);

    LOGD("onGPSStateChange = {type=%d, length=%d}", extra_gps_tlv->type, extra_gps_tlv->length);
    if (extra_gps_tlv->type == 0)
    {
        s_gps_state = 0;
        if (oldState == 0)
            return;
        if (ql_is_mc20_gps)
            at_send_command("AT+QGNSSC=0", NULL);
        else
            at_send_command("AT+QGPSEND", NULL);
    } 
    else if (extra_gps_tlv->type == 1)
    {
        s_gps_state = 1;
        if (oldState != 0) {
            if (ql_is_mc20_gps && s_poll_pending == 0) {
                s_poll_pending = 1;
                GPS_requestTimedCallback (pollNMEAReader, NULL, &TIMEVAL_1);
            }
            return;
        }

        if (!ql_is_mc20_gps && s_last_inject_xtra_data != NULL)
        {
            struct tm tm;
            time_t now = time(NULL);

            if (s_last_inject_time > now)
                now = s_last_inject_time;
            gmtime_r(&now, &tm);
  
            at_send_command("AT+QGPSXTRATAUTO=0", NULL);
            at_send_command("AT+QGPSXTRA=1", NULL);
            at_send_command("AT+QFDEL=\"RAM:xtra2.bin\"", NULL);
            
            asprintf(&cmd, "AT+QFUPL=\"RAM:xtra2.bin\",%d,%d", s_last_inject_xtra_length, 60);
            at_send_command_raw(cmd, s_last_inject_xtra_data, s_last_inject_xtra_length, "+QFUPL:", NULL);
            free(cmd);    
            
            asprintf(&cmd, "AT+QGPSXTRATIME=0, \"%d/%d/%d,%d:%d:%d\",1,1,%d",
                tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, s_last_inject_uncertainty);
            at_send_command(cmd, NULL);
            free(cmd);    
            
            at_send_command("AT+QGPSXTRADATA=\"RAM:xtra2.bin\"", NULL);
            at_send_command("AT+QFDEL=\"RAM:xtra2.bin\"", NULL);
            free(s_last_inject_xtra_data);
            s_last_inject_xtra_data = NULL;

            s_agps_check_times = 15;
            GPS_requestTimedCallback (pollXTRAStateChange, NULL, &TIMEVAL_1);
        }
        else if (s_last_inject_xtra_data != NULL)
        {       
            free(s_last_inject_xtra_data);
            s_last_inject_xtra_data = NULL;      
        }

        if (ql_is_mc20_gps) {
            p_response = NULL;
            err = at_send_command("AT+QGNSSC=1", &p_response);
            if (err == 0 && p_response != NULL && p_response->success == 1) {
                s_poll_pending = 1;
                GPS_requestTimedCallback (pollNMEAReader, NULL, &TIMEVAL_1);
            }
            at_response_free(p_response);
        } else
            at_send_command("AT+QGPS=1", NULL);
    }
    else if (extra_gps_tlv->type == 23)
    { //inject time
        /** Milliseconds since January 1, 1970 */
        typedef int64_t GpsUtcTime;
        GpsUtcTime gpsutctime; int64_t timeReference; int uncertainty;
        struct tm tm;
        
        memcpy(&gpsutctime, extra_gps_tlv->data, sizeof(gpsutctime));
        memcpy(&timeReference, extra_gps_tlv->data + sizeof(gpsutctime), sizeof(timeReference));
        memcpy(&uncertainty, extra_gps_tlv->data + sizeof(gpsutctime) + sizeof(uncertainty), sizeof(uncertainty));
            
        LOGD("%s(time=%lld, timeReference=%lld, uncertainty=%d)",__FUNCTION__,
            *((int64_t *)&gpsutctime), timeReference, uncertainty);
        
        s_last_inject_time = (gpsutctime+999)/1000;
        s_last_inject_uncertainty = uncertainty;

        gmtime_r(&s_last_inject_time, &tm);

        LOGD("%s GpsUtcTime: \"%d/%d/%d,%d:%d:%d\", uncertainty=%d", __func__,
                tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, s_last_inject_uncertainty);
    }
    else if (extra_gps_tlv->type == 34) 
    { //inject xtra
        if (s_last_inject_xtra_data)
            free(s_last_inject_xtra_data);

        s_last_inject_xtra_data = malloc(extra_gps_tlv->length);
        s_last_inject_xtra_length = extra_gps_tlv->length;
        if (s_last_inject_xtra_data != NULL)
            memcpy(s_last_inject_xtra_data, extra_gps_tlv->data, extra_gps_tlv->length);
    }

    free(extra_gps_tlv);
}

static void * GpsMainLoop(void *param) {
    struct sockaddr_un addr;
    struct sockaddr_un *p_addr = &addr;
    const char *name = "rild-gps";
    int type = SOCK_STREAM;
    int n;
    int err;
    
    int s = socket(AF_LOCAL, type, 0);
    if (s < 0) return NULL;

    memset (p_addr, 0, sizeof (*p_addr));
    p_addr->sun_family = AF_LOCAL;
    p_addr->sun_path[0] = 0;
    memcpy(p_addr->sun_path + 1, name, strlen(name) );

    n = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(n));

    if (bind(s, (struct sockaddr *) &addr,  strlen(name) + offsetof(struct sockaddr_un, sun_path) + 1) < 0) {
        return NULL;
    }

    if (type == SOCK_STREAM) {
        int ret;

        ret = listen(s, 1);

        if (ret < 0) {
            close(s);
            return NULL;
        }
    }

    for(;;) {
        struct sockaddr addr;
        socklen_t alen;
        int fd;
        int ret;
        struct pollfd pollfds[1];
        GPS_TLV gps_tlv;
        GPS_TLV *extra_gps_tlv = NULL;

        alen = sizeof(addr);
        LOGD("waiting for /system/lib/hw/gps.default.so connect rild-gps");
        fd = accept(s, &addr, &alen);
        if(fd < 0) {
            LOGD("accept failed: %s\n", strerror(errno));
            continue;
        }

        fcntl(fd, F_SETFD, FD_CLOEXEC);

        //LOGD("reading gps cmd");
        fcntl(fd, F_SETFL, O_NONBLOCK);

        pollfds[0].fd = fd;
        pollfds[0].events = POLLIN;
        pollfds[0].revents = 0;
        gps_tlv.type = -1;
        gps_tlv.length = 0;
        extra_gps_tlv = NULL;

        do {
            do {
                ret = poll(pollfds, 1, -1);
            } while ((ret < 0) && (errno == EINTR));

            if (pollfds[0].revents & POLLIN) {
                ssize_t nreads;
                if (gps_tlv.length == 0) {
                    nreads = read(fd, &gps_tlv, sizeof(gps_tlv));
                    if (nreads <= 0) {
                        LOGE("%s read=%d errno: %d (%s)",  __func__, (int)nreads, errno, strerror(errno));
                        break;
                    }

                    if (nreads == 1) { //old gps hal only send gps_cmd
                        unsigned char gps_cmd = *((unsigned char *)&gps_tlv);
                        gps_tlv.type = gps_cmd;
                        gps_tlv.length = 0;
                    } 

                    //gps_tlv->length is the length of data want to read
                    //extra_gps_tlv->length is the length of data had read
                    extra_gps_tlv = (GPS_TLV *)malloc(sizeof(gps_tlv) + gps_tlv.length);
                    extra_gps_tlv->type = gps_tlv.type;
                    extra_gps_tlv->length = 0;
                } else {
                    nreads = read(fd, extra_gps_tlv->data + extra_gps_tlv->length, gps_tlv.length);
                    if (nreads <= 0) {
                        LOGE("%s read=%d errno: %d (%s)",  __func__, (int)nreads, errno, strerror(errno));
                        break;
                    }  
                    extra_gps_tlv->length += nreads;
                    gps_tlv.length -= nreads;
                }
            }
            else if (pollfds[0].revents & (POLLERR | POLLHUP | POLLNVAL)) {
                break;
            }
        }
        while (gps_tlv.length);

        LOGD("gps_tlv = {type=%d, length=%d}", gps_tlv.type, gps_tlv.length);
        if (extra_gps_tlv) {
            LOGD("extra_gps_tlv = {type=%d, length=%d}", extra_gps_tlv->type, extra_gps_tlv->length);
        }

        if (extra_gps_tlv) {
            GPS_requestTimedCallback (onGPSStateChange, extra_gps_tlv, NULL);
        }
done:
        close(fd);
    }

    return NULL;
}

static void * GpsNmeaLoop(void *param) {
    struct sockaddr_un addr;
    struct sockaddr_un *p_addr = &addr;
    const char *name = "rild-nmea";
    int type = SOCK_STREAM;
    int n;
    int err;
    
    int s = socket(AF_LOCAL, type, 0);
    if (s < 0) return NULL;

    memset (p_addr, 0, sizeof (*p_addr));
    p_addr->sun_family = AF_LOCAL;
    p_addr->sun_path[0] = 0;
    memcpy(p_addr->sun_path + 1, name, strlen(name) );

    n = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(n));

    if (bind(s, (struct sockaddr *) &addr,  strlen(name) + offsetof(struct sockaddr_un, sun_path) + 1) < 0) {
        return NULL;
    }

    if (type == SOCK_STREAM) {
        int ret;

        ret = listen(s, 1);

        if (ret < 0) {
            close(s);
            return NULL;
        }
    }

    for(;;) {
        struct sockaddr addr;
        socklen_t alen;
        int fd;
        int ret;
        struct pollfd pollfds[2];

        alen = sizeof(addr);
        LOGD("waiting for /system/lib/hw/gps.default.so connect rild-nmea");
        fd = accept(s, &addr, &alen);
        if(fd < 0) {
            LOGD("accept failed: %s\n", strerror(errno));
            continue;
        }

        fcntl(fd, F_SETFD, FD_CLOEXEC);

        fcntl(fd, F_SETFL, O_NONBLOCK);

        pollfds[0].fd = fd;
        pollfds[0].events = POLLIN;
        pollfds[0].revents = 0;
        
        ql_mc20_nmea_client = fd;
        LOGD("ql_mc20_nmea_client fd = %d connect!", ql_mc20_nmea_client);
        do {
            do {
                ret = poll(pollfds, 1, -1);
            } while ((ret < 0) && (errno == EINTR));

            if (pollfds[0].revents & POLLIN) {
                char tmp[128];
                ssize_t nreads = 0;
                nreads = read(fd, tmp, sizeof(tmp)-1);
                if (nreads > 0) {
                    tmp[nreads] = 0;
                    LOGD("recevie nema cmd: %s", tmp);
                    if (!strcmp(tmp, "close rild-nema")) {
                        goto done;
                    }
                }
            }
            else if (pollfds[0].revents & (POLLERR | POLLHUP | POLLNVAL)) {
                break;
            }
        } while (1);
        LOGD("ql_mc20_nmea_client fd = %d disconnect!", ql_mc20_nmea_client);
        ql_mc20_nmea_client = -1;

done:
        close(fd);
    }

    return NULL;
}

static void * GpsControlLoop(void *param) {
    GPS_EVENT gps_event;
    int i, ret;
    int fd = ql_gps_control[0];
    struct pollfd pollfds[1];

    fcntl(fd, F_SETFD, FD_CLOEXEC);
    fcntl(fd, F_SETFL, O_NONBLOCK);
    
    do {
        pollfds[0].fd = fd;
        pollfds[0].events = POLLIN;
        pollfds[0].revents = 0;
        long expire_msec = 36000*1000L;
        long now_msec;
        struct timeval tv;
        gettimeofday(&tv, (struct timezone *) NULL);
        now_msec = tv.tv_sec*1000 + tv.tv_usec/1000;
            
        for (i = 0; i < sizeof(s_gps_events)/sizeof(s_gps_events[0]); i++) {           
            long tmp = s_gps_events[i].expire_msec - now_msec;
            if (s_gps_events[i].callback == 0)
                continue;
            //LOGD("%s callback=%p, time=%ld", __func__, s_gps_events[i].callback, tmp);
            if (tmp < 100) {
                s_gps_events[i].callback(s_gps_events[i].param);
                memset(&s_gps_events[i], 0x00, sizeof(s_gps_events[i]));
                tmp = 0;
            }

            if (0 < tmp && tmp < expire_msec)
                expire_msec = tmp ;
        }

        //LOGD("%s expire_msec=%ld", __func__, expire_msec);

        do {
            ret = poll(pollfds, 1, expire_msec > 0 ? expire_msec : -1);
        } while ((ret < 0) && (errno == EINTR));

        if (pollfds[0].revents & POLLIN) {
            if (read(fd, &gps_event, sizeof(gps_event)) == sizeof(gps_event)) {
                for (i = 0; i < sizeof(s_gps_events)/sizeof(s_gps_events[0]); i++) {
                    if (gps_event.callback == s_gps_events[i].callback) {
                        if (gps_event.expire_msec < s_gps_events[i].expire_msec)
                            s_gps_events[i].expire_msec = gps_event.expire_msec;
                        break;
                    }
                }

                if (i == sizeof(s_gps_events)/sizeof(s_gps_events[0])) {
                    for (i = 0; i < sizeof(s_gps_events)/sizeof(s_gps_events[0]); i++) {
                        if (0 == s_gps_events[i].callback) {
                            s_gps_events[i] = gps_event;
                            break;
                        }
                    }
                }
            }

        }
        else if (pollfds[0].revents & (POLLERR | POLLHUP | POLLNVAL)) {
            break;
        }
    } while (1);
        
    LOGD("%s exit", __func__);
    return NULL;
}

void ql_gps_init(const char *module_version) {
    if (ql_gps_control[0] == 0)
        socketpair( AF_LOCAL, SOCK_STREAM, 0, ql_gps_control);
    ql_is_mc20_gps = !strncmp(module_version, "MC", 2);
    if (s_control_thread == 0) {
        pthread_create(&s_control_thread, NULL, GpsControlLoop, NULL);     
    }
    if (s_gps_thread == 0) {
        pthread_create(&s_gps_thread, NULL, GpsMainLoop, NULL);     
    }
    if (ql_is_mc20_gps && s_nmea_thread == 0) {
        pthread_create(&s_nmea_thread, NULL, GpsNmeaLoop, NULL);
    }   
    if (ql_is_mc20_gps && s_gps_state) {
        at_send_command("AT+QGNSSC=1", NULL);
        if (s_poll_pending == 0) {
            s_poll_pending = 1;
            GPS_requestTimedCallback (pollNMEAReader, NULL, &TIMEVAL_1);
        }
    }    
}
