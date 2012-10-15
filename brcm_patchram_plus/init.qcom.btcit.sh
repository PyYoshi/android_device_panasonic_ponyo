#!/system/bin/sh
# AzureWave. Inc 2010/07/23 modify for Broadcom BCM43xx
# SIM(smartwireless.cn ONLY; Confidential Note

LOG_TAG="qcom-bluetooth"
LOG_NAME="${0}:"

loge ()
{
  /system/bin/log -t $LOG_TAG -p e "$LOG_NAME $@"
}

logi ()
{
  /system/bin/log -t $LOG_TAG -p i "$LOG_NAME $@"
}
echo 1 > /sys/devices/platform/bt_power/rfkill/rfkill0/state

logi "+BCM4330 entered HCIT mode"
cd /system/bin
./brcm_patchram_plus.dat --enable_tst -d --patchram /etc/BCM4330.hcd /dev/ttyHS0
logi "-BCM4330 entered HCIT mode"
exit 0
