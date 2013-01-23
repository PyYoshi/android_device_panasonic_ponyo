#!/bin/sh

VENDOR=panasonic
DEVICE=ponyo

BASE=../../../vendor/$VENDOR/$DEVICE/proprietary
rm -rf $BASE/*

for FILE in `cat proprietary-files.txt | grep -v ^# | grep -v ^$`; do
    DIR=`dirname $FILE`
    if [ ! -d $BASE/$DIR ]; then
        mkdir -p $BASE/$DIR
    fi
    adb pull /system/$FILE $BASE/$FILE
done

adb pull /system/lib/lights.msm7k.so $BASE/lib/lights.qcom.so

./setup-makefiles.sh
