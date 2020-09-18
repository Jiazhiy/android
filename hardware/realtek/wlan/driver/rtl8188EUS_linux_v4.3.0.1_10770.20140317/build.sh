#!/bin/sh
make ARCH=arm clean
make ARCH=arm modules -j4
cp wlan.ko ../../../../../hardware/samsung_slsi/slsiap/prebuilt/modules/
