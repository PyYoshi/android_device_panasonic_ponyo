#!/system/bin/sh

LOG_TAG="nvram-generator"
LOG_NAME="${0}:"

loge ()
{
  /system/bin/log -t $LOG_TAG -p e "$LOG_NAME $@"
}

logi ()
{
  /system/bin/log -t $LOG_TAG -p i "$LOG_NAME $@"
}

logi "Generating nvram.txt ..."

macAddrsFile="/data/simcom/macAddr/wlan_macAddr"
inNvramPath="/system/etc/firmware/wlan/nvram.txt"
outNvramPath="/data/simcom/nvram.txt"

BUFIFS=$IFS
IFS=

# NVRAMの生成
exec 3<${macAddrsFile}
while read FL 0<&3
do
    cat ${inNvramPath} | sed "s/00:90:4c:c5:12:38/${FL}/" > ${outNvramPath}
    break
done

chmod 0666 ${outNvramPath}
chown system.system ${outNvramPath}

exit 0