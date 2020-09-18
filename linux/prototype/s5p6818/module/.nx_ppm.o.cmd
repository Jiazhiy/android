cmd_arch/arm/mach-s5p6818/prototype/module/nx_ppm.o := arm-eabi-gcc -Wp,-MD,arch/arm/mach-s5p6818/prototype/module/.nx_ppm.o.d  -nostdinc -isystem /home/topeet/4418/ykt/android/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include -I/home/topeet/4418/ykt/android/linux/kernel/kernel-3.4.39/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include /home/topeet/4418/ykt/android/linux/kernel/kernel-3.4.39/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-s5p6818/include -Iarch/arm/plat-s5p6818/include -I/home/topeet/4418/ykt/android/linux/kernel/kernel-3.4.39/arch/arm/plat-s5p6818/common -I/home/topeet/4418/ykt/android/linux/kernel/kernel-3.4.39/arch/arm/plat-s5p6818/topeet/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -marm -fno-dwarf2-cfi-asm -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -I/home/topeet/4418/ykt/android/linux/kernel/kernel-3.4.39/arch/arm/mach-s5p6818/prototype/base -I/home/topeet/4418/ykt/android/linux/kernel/kernel-3.4.39/arch/arm/mach-s5p6818/prototype/module -I/home/topeet/4418/ykt/android/linux/kernel/kernel-3.4.39/arch/arm/mach-s5p6818/prototype/module -D__LINUX__ -D__PRINTK__ -DNX_RELEASE -mfpu=vfp -mfloat-abi=softfp -I/home/topeet/4418/ykt/android/linux/kernel/kernel-3.4.39/arch/arm/plat-s5p6818/common -I/home/topeet/4418/ykt/android/linux/kernel/kernel-3.4.39/arch/arm/plat-s5p6818/topeet/include -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -I/home/topeet/4418/ykt/android/linux/kernel/kernel-3.4.39/prototype/base -I/home/topeet/4418/ykt/android/linux/kernel/kernel-3.4.39/prototype/module -I/home/topeet/4418/ykt/android/linux/kernel/kernel-3.4.39/prototype/module -D__LINUX__ -D__PRINTK__ -DNX_RELEASE -mfpu=vfp -mfloat-abi=softfp    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(nx_ppm)"  -D"KBUILD_MODNAME=KBUILD_STR(nx_ppm)" -c -o arch/arm/mach-s5p6818/prototype/module/nx_ppm.o arch/arm/mach-s5p6818/prototype/module/nx_ppm.c

source_arch/arm/mach-s5p6818/prototype/module/nx_ppm.o := arch/arm/mach-s5p6818/prototype/module/nx_ppm.c

deps_arch/arm/mach-s5p6818/prototype/module/nx_ppm.o := \
  /home/topeet/4418/ykt/android/linux/kernel/kernel-3.4.39/arch/arm/mach-s5p6818/prototype/base/nx_chip.h \
  arch/arm/mach-s5p6818/prototype/module/nx_ppm.h \
  arch/arm/mach-s5p6818/prototype/module/../base/nx_prototype.h \
  arch/arm/mach-s5p6818/prototype/module/../base/nx_type.h \
  arch/arm/mach-s5p6818/prototype/module/../base/nx_debug.h \
  arch/arm/mach-s5p6818/prototype/module/../base/nx_chip.h \
  arch/arm/mach-s5p6818/prototype/module/../base/nx_clockcontrol.h \
  arch/arm/mach-s5p6818/prototype/module/../base/nx_bit_accessor.h \

arch/arm/mach-s5p6818/prototype/module/nx_ppm.o: $(deps_arch/arm/mach-s5p6818/prototype/module/nx_ppm.o)

$(deps_arch/arm/mach-s5p6818/prototype/module/nx_ppm.o):
