#!/system/bin/sh

LOG_TAG="nvram_generator"
LOG_NAME="${0}:"

loge ()
{
  /system/bin/log -t $LOG_TAG -p e "$LOG_NAME $@"
}

logi ()
{
  /system/bin/log -t $LOG_TAG -p i "$LOG_NAME $@"
}

inNvramPath="/system/etc/firmware/wlan/nvram.txt"
outNvramPath="/data/simcom/nvram.txt"
macAddrsFile="/data/simcom/macAddr/wlan_macAddr"

if [ ! -e ${outNvramPath} ]
then
    if [ ! -e ${macAddrsFile} ]
    then
        logi "Generating MAC Address files ..."
        /system/bin/hwaddrs > /dev/null 2>&1
    fi
    
    logi "Generating nvram.txt ..."
    BUFIFS=$IFS
    IFS=
    exec 3<${macAddrsFile}
    
    while read FL 0<&3
    do
        cat ${inNvramPath} | sed "s/00:90:4c:c5:12:38/${FL}/" > ${outNvramPath}
        break
    done
    
    if [ ! -e ${outNvramPath} ]
    then
        cp ${inNvramPath} ${outNvramPath}
    fi
    
    chmod 0666 ${outNvramPath}
    chown system.system ${outNvramPath}
fi

exit 0
