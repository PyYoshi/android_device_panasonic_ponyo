#!/system/bin/sh

LOG_TAG="macAddr-generator"
LOG_NAME="${0}:"

loge ()
{
  /system/bin/log -t $LOG_TAG -p e "$LOG_NAME $@"
}

logi ()
{
  /system/bin/log -t $LOG_TAG -p i "$LOG_NAME $@"
}

macAddrsFile="/data/simcom/macAddr/wlan_macAddr"
outMacAddrsFile="/data/simcom/macAddr/mac_addr.file"

logi "Generating MAC Address files ..."

# MAC Addressの生成
/system/bin/hwaddrs

# Kernelが必要とするファイルの生成
cat ${macAddrsFile} | sed -e "s/://g" > ${outMacAddrsFile}

chmod 0666 ${outMacAddrsFile}
chown system.system ${outMacAddrsFile}

/system/bin/sh /system/bin/generate_nvram.sh

exit 0