cmd_arch/arm/cpu/slsiap/s5p4418/prototype/module/nx_wdt.o := arm-eabi-gcc -Wp,-MD,arch/arm/cpu/slsiap/s5p4418/prototype/module/.nx_wdt.o.d  -nostdinc -isystem /home/topeet/android/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include -Iinclude  -I/home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/include -D__KERNEL__ -DCONFIG_SYS_TEXT_BASE=0x42C00000 -Wall -Wstrict-prototypes -Wno-format-security -fno-builtin -ffreestanding -mcpu=cortex-a9 -Os -fno-stack-protector -g -fstack-usage -Wno-format-nonliteral -DCONFIG_ARM -D__ARM__ -marm -mno-thumb-interwork -mabi=aapcs-linux -mword-relocations -march=armv7-a -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -Wno-unused-but-set-variable -mcpu=cortex-a9 -fno-short-enums -fstrict-aliasing -I/home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/s5p4418/prototype/module -I/home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/s5p4418/prototype/base -I/home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/include/asm/arch-s5p4418 -I/home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/common -I/home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/devices -I/home/topeet/android/linux/bootloader/u-boot-2014.07/board/s5p4418/common -D__LINUX__ -DNX_RELEASE -D__SUPPORT_MIO_UBOOT__ -D__SUPPORT_MIO_UBOOT_CHIP_S5P4418__ -I/home/topeet/android/linux/bootloader/u-boot-2014.07/board/s5p4418/drone2/include -pipe    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(nx_wdt)"  -D"KBUILD_MODNAME=KBUILD_STR(nx_wdt)" -c -o arch/arm/cpu/slsiap/s5p4418/prototype/module/nx_wdt.o arch/arm/cpu/slsiap/s5p4418/prototype/module/nx_wdt.c

source_arch/arm/cpu/slsiap/s5p4418/prototype/module/nx_wdt.o := arch/arm/cpu/slsiap/s5p4418/prototype/module/nx_wdt.c

deps_arch/arm/cpu/slsiap/s5p4418/prototype/module/nx_wdt.o := \
  /home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/s5p4418/prototype/base/nx_chip.h \
  /home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/s5p4418/prototype/module/nx_wdt.h \
  /home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/s5p4418/prototype/base/nx_prototype.h \
  /home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/s5p4418/prototype/base/nx_type.h \
  /home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/s5p4418/prototype/base/nx_debug.h \
  /home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/s5p4418/prototype/base/nx_chip.h \
  /home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/s5p4418/prototype/base/nx_clockcontrol.h \
  /home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/s5p4418/prototype/base/nx_bit_accessor.h \
  /home/topeet/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/s5p4418/prototype/base/nx_type.h \

arch/arm/cpu/slsiap/s5p4418/prototype/module/nx_wdt.o: $(deps_arch/arm/cpu/slsiap/s5p4418/prototype/module/nx_wdt.o)

$(deps_arch/arm/cpu/slsiap/s5p4418/prototype/module/nx_wdt.o):
