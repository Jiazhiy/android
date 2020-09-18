#!/bin/sh
make ARCH=arm clean
make ARCH=arm modules -j4
