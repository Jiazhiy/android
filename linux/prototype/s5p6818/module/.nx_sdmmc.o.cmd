cmd_arch/arm/cpu/slsiap/s5p6818/prototype/module/nx_sdmmc.o := arm-eabi-gcc -Wp,-MD,arch/arm/cpu/slsiap/s5p6818/prototype/module/.nx_sdmmc.o.d  -nostdinc -isystem /home/topeet/4418/ykt/android/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include -Iinclude  -I/home/topeet/4418/ykt/android/linux/bootloader/u-boot-2014.07/arch/arm/include -D__KERNEL__ -DCONFIG_SYS_TEXT_BASE=0x43C00000 -Wall -Wstrict-prototypes -Wno-format-security -fno-builtin -ffreestanding -mcpu=cortex-a9 -Os -fno-stack-protector -g -fstack-usage -Wno-format-nonliteral -DCONFIG_ARM -D__ARM__ -marm -mno-thumb-interwork -mabi=aapcs-linux -mword-relocations -ffunction-sections -fdata-sections -fno-common -ffixed-r9 -Wno-unused-but-set-variable -fno-short-enums -fstrict-aliasing -Wno-unused-but-set-variable -I/home/topeet/4418/ykt/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/s5p6818/prototype/module -I/home/topeet/4418/ykt/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/s5p6818/prototype/base -I/home/topeet/4418/ykt/android/linux/bootloader/u-boot-2014.07/arch/arm/include/asm/arch-s5p6818 -I/home/topeet/4418/ykt/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/common -I/home/topeet/4418/ykt/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/devices -I/home/topeet/4418/ykt/android/linux/bootloader/u-boot-2014.07/board/s5p6818/common -D__LINUX__ -DNX_RELEASE -I/home/topeet/4418/ykt/android/linux/bootloader/u-boot-2014.07/board/s5p6818/dronel/include -pipe    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(nx_sdmmc)"  -D"KBUILD_MODNAME=KBUILD_STR(nx_sdmmc)" -c -o arch/arm/cpu/slsiap/s5p6818/prototype/module/nx_sdmmc.o arch/arm/cpu/slsiap/s5p6818/prototype/module/nx_sdmmc.c

source_arch/arm/cpu/slsiap/s5p6818/prototype/module/nx_sdmmc.o := arch/arm/cpu/slsiap/s5p6818/prototype/module/nx_sdmmc.c

deps_arch/arm/cpu/slsiap/s5p6818/prototype/module/nx_sdmmc.o := \
  /home/topeet/4418/ykt/android/linux/bootloader/u-boot-2014.07/arch/arm/cpu/slsiap/s5p6818/prototype/base/nx_chip.h \
  arch/arm/cpu/slsiap/s5p6818/prototype/module/nx_sdmmc.h \
  arch/arm/cpu/slsiap/s5p6818/prototype/module/../base/nx_prototype.h \
  arch/arm/cpu/slsiap/s5p6818/prototype/module/../base/nx_type.h \
  arch/arm/cpu/slsiap/s5p6818/prototype/module/../base/nx_debug.h \
  arch/arm/cpu/slsiap/s5p6818/prototype/module/../base/nx_chip.h \
  arch/arm/cpu/slsiap/s5p6818/prototype/module/../base/nx_clockcontrol.h \
  arch/arm/cpu/slsiap/s5p6818/prototype/module/../base/nx_bit_accessor.h \

arch/arm/cpu/slsiap/s5p6818/prototype/module/nx_sdmmc.o: $(deps_arch/arm/cpu/slsiap/s5p6818/prototype/module/nx_sdmmc.o)

$(deps_arch/arm/cpu/slsiap/s5p6818/prototype/module/nx_sdmmc.o):
