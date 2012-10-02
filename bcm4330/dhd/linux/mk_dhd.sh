#!/bin/bash
make -j4 ARCH=arm CROSS_COMPILE=$CCOMPILER LINUXDIR=$KERNEL_DIR dhd-cdc-sdmmc-gpl-debug