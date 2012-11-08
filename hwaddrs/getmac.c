/*
 * Copyright (C) 2011-2012 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <fcntl.h>
#include <utils/Log.h>

#define LOG_TAG "hwaddrs"

extern void nv_cmd_remote(int,int,void*);
extern void oncrpc_init();
extern void oncrpc_deinit();
extern void oncrpc_task_start();
extern void oncrpc_task_stop();

int main() {
    FILE *fd_wlan;
    int wlanmac[2] = { 0, };

    oncrpc_init();
    oncrpc_task_start();
    nv_cmd_remote(0,0x1246,&wlanmac);
    oncrpc_task_stop();
    oncrpc_deinit();

    if (wlanmac[0] == 0)
        return 0;

    LOGD("WLAN MAC Address: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
        wlanmac[0]&0xFF,
        (wlanmac[0]&0xFF00) >> 8,
        (wlanmac[0]&0xFF0000) >> 16,
        (wlanmac[0]&0xFF000000) >> 24,
        wlanmac[1]&0xFF,
        (wlanmac[1]&0xFF00) >> 8
    );

    fd_wlan = fopen("/data/simcom/macAddr/wlan_macAddr","w");
    fprintf(fd_wlan,"%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
        wlanmac[0]&0xFF,
        (wlanmac[0]&0xFF00) >> 8,
        (wlanmac[0]&0xFF0000) >> 16,
        ((wlanmac[0]&0xFF000000) >> 24) - 0x03,
        wlanmac[1]&0xFF,
        (wlanmac[1]&0xFF00) >> 8
    );
    fclose(fd_wlan);

    // WLAN MACアドレスの4オクテット目を-0x03してる？
    LOGD("Bluetooth MAC Address: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
        wlanmac[0]&0xFF,
        (wlanmac[0]&0xFF00) >> 8,
        (wlanmac[0]&0xFF0000) >> 16,
        ((wlanmac[0]&0xFF000000) >> 24) - 0x03,
        wlanmac[1]&0xFF,
        (wlanmac[1]&0xFF00) >> 8
    );

    FILE *fd_bt;

    fd_bt = fopen("/data/simcom/btadd/bt_macAddr","w");
    fprintf(fd_bt,"%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
        (wlanmac[1]&0xFF00) >> 8,
        wlanmac[1]&0xFF,
        ((wlanmac[0]&0xFF000000) >> 24) - 3,
        (wlanmac[0]&0xFF0000) >> 16,
        (wlanmac[0]&0xFF00) >> 8, 
        wlanmac[0]&0xFF
    );
    fclose(fd_bt);

    return 0;
}

