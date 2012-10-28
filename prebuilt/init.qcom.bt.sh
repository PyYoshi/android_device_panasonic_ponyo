#!/system/bin/sh
# 2011/03/29 modify for Broadcom BCM4330 BlueTooth
# SIM(smartwireless.cn ONLY; Confidential Note


BLUETOOTH_SLEEP_PATH=/proc/bluetooth/sleep/proto
LOG_TAG="qcom-bluetooth"
LOG_NAME="${0}:"

hciattach_pid=""

loge ()
{
  /system/bin/log -t $LOG_TAG -p e "$LOG_NAME $@"
}

logi ()
{
  /system/bin/log -t $LOG_TAG -p i "$LOG_NAME $@"
}

failed ()
{
  loge "$1: exit code $2"
  exit $2
}

start_hciattach ()
{
  echo 1 > $BLUETOOTH_SLEEP_PATH
  /system/bin/hciattach -n /dev/ttyHS0 any 3000000 flow &
  #/system/bin/hciattach /dev/ttyHS0 any 115200 flow &
  hciattach_pid=$!
  logi "start_hciattach: pid = $hciattach_pid"
}

kill_hciattach ()
{
  logi "kill_hciattach: pid = $hciattach_pid"
  ## careful not to kill zero or null!
  kill -TERM $hciattach_pid
  echo 0 > $BLUETOOTH_SLEEP_PATH
  # this shell doesn't exit now -- wait returns for normal exit
}

cd /system/bin
logi "Starting to patchram for BCM4330..."
./brcm_patchram_plus -d --enable_lpm --patchram /etc/BCM4330.hcd /dev/ttyHS0
logi "Change baudrate to 3000000"
./brcm_patchram_plus -d -baudrate 3000000 /dev/ttyHS0 
exit_code_hci_qcomm_download=$?

case $exit_code_hci_qcomm_download in
  0) logi "Bluetooth BCM4330 firmware download succeeded";;
  *) failed "Bluetooth BCM4330 firmware download failed" $exit_code_hci_qcomm_download;;
esac

# init does SIGTERM on ctl.stop for service
trap "kill_hciattach" TERM INT

start_hciattach

wait $hciattach_pid

exit 0
