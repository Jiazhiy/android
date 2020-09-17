LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	main.c \
	magic.c \
	fsm.c \
	lcp.c \
	ipcp.c \
	upap.c \
	chap-new.c \
	ccp.c \
	ecp.c \
	auth.c \
	options.c \
	sys-linux.c \
	chap_ms.c \
	demand.c \
	utils.c \
	tty.c \
	eap.c \
	chap-md5.c \
	pppcrypt.c \
	openssl-hash.c \
	pppox.c

LOCAL_SHARED_LIBRARIES := \
	libcutils liblog libcrypto

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/include

LOCAL_CFLAGS := -DANDROID_CHANGES -DCHAPMS=1 -DMPPE=1 -Iexternal/openssl/include

LOCAL_MODULE:= pppd

include $(BUILD_EXECUTABLE)

#add by cym 20150922
include $(CLEAR_VARS)
LOCAL_SRC_FILES := chat.c
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_MODULE := chat
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := ip-up-ppp0.c
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_MODULE := ip-up-ppp0
LOCAL_MODULE_PATH := $(TARGET_OUT_ETC)/ppp
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)
#end add
