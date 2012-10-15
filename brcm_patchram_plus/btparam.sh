freq=$1
type=$2

loge ()
{
  /system/bin/log -t $LOG_TAG -p e "$LOG_NAME $@"
}

echo 1 > /sys/devices/platform/bt_power/rfkill/rfkill0/state
/system/bin/brcm_afh_tx_test -d --patchram /etc/BCM4330.hcd --frequency $freq --pkttype $type /dev/ttyHS0
exit_bttestt=$?

case $exit_bttestt in
    0) loge "BT test with param START succeeded";;
    *) loge "BT test with param START failed";;
esac 

echo 0 > /sys/devices/platform/bt_power/rfkill/rfkill0/state

