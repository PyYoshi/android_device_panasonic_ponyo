/*
 * Copyright (C) 2008 The Android Open Source Project
 * Copyright (C) 2011 Diogo Ferreira <defer@cyanogenmod.com>
 * Copyright (C) 2011 The CyanogenMod Project <http://www.cyanogenmod.com>
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

#ifndef bool
    #define bool int
#endif

#ifndef true
    #define true 1
#endif

#ifndef false
    #define false 0
#endif

#define LOG_TAG "lights.ponyo"

#include <cutils/log.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>

#include <sys/ioctl.h>
#include <sys/types.h>

#include <hardware/lights.h>
#include "lights.h"

#define LED_COLORS_MAX_BRIGHTNESS 40
#define LED_BACKLIGHT_MAX_BRIGHTNESS 255

enum {
    LED_RED,
    LED_GREEN,
    LED_BLUE,
    LED_BLANK,
};

static pthread_once_t g_init = PTHREAD_ONCE_INIT;
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

static int write_int(const char *path, int value) {
    int fd;
    static int already_warned = 0;

    fd = open(path, O_RDWR);
    if (fd < 0) {
        if (already_warned == 0) {
            ALOGE("write_int failed to open %s\n", path);
            already_warned = 1;
        }
        return -errno;
    }

    //LOGD("write_int wrote: %s, %d", path, value);
    char buffer[20];
    int bytes = snprintf(buffer, sizeof(buffer), "%d\n", value);
    int written = write(fd, buffer, bytes);
    close(fd);

    return written == -1 ? -errno : 0;
}

static int write_blink(int color, bool on, int value) {
    const char *blink_path;
    int ret = 0;
    switch(color){
        case LED_RED:
            if(on){
                blink_path = RED_BLINK_ON_FILE;
            }else{
                blink_path = RED_BLINK_OFF_FILE;
            }
            break;
        case LED_GREEN:
            if(on){
                blink_path = GREEN_BLINK_ON_FILE;   
            }else{
                blink_path = GREEN_BLINK_OFF_FILE;
            }
            break;
        case LED_BLUE:
            if(on){
                blink_path = BLUE_BLINK_ON_FILE;
            }else{
                blink_path = BLUE_BLINK_OFF_FILE;   
            }
            break;
        default:
            return -EINVAL;
    }
    pthread_mutex_lock(&g_lock);
    ret = write_int(blink_path, value);
    pthread_mutex_unlock(&g_lock);
    return ret;
}

static int write_blink_on_off(int color, int on_value, int off_value){
    int ret = 0;
    ret = write_blink(color, true, on_value);
    if(ret < 0){
        return ret;
    }
    ret = write_blink(color, false, off_value);
    return ret;
}

static int write_blink_for_rgb(int on_value, int off_value){
    int ret = 0;
    ret = write_blink_on_off(LED_RED, on_value, off_value);
    if(ret < 0){
        return ret;
    }
    ret = write_blink_on_off(LED_GREEN, on_value, off_value);
    if(ret < 0){
        return ret;
    }
    ret = write_blink_on_off(LED_BLUE, on_value, off_value);
    return ret;
}

static int write_brightness(int color, int value){
    int ret = 0;
    const char *path;
    int limited_brightness = (value*LED_COLORS_MAX_BRIGHTNESS)>>8;
    switch(color){
        case LED_RED:
            path = RED_LED_FILE;
            break;
        case LED_GREEN:
            path = GREEN_LED_FILE;
            break;
        case LED_BLUE:
            path = BLUE_LED_FILE;
            break;
        default:
            return -EINVAL;
    }

    pthread_mutex_lock(&g_lock);
    ret = write_int(path, limited_brightness);
    pthread_mutex_unlock(&g_lock);
    
    return ret;
}
        
void init_globals(void) {
    pthread_mutex_init(&g_lock, NULL);
}

static int rgb_to_brightness(struct light_state_t const* state) {
    int color = state->color & 0x00ffffff;
    return ((77*((color>>16)&0x00ff))
            + (150*((color>>8)&0x00ff)) + (29*(color&0x00ff))) >> 8;
}

static int set_light_backlight(struct light_device_t *dev, struct light_state_t const *state) {
    int err = 0;
    int brightness = rgb_to_brightness(state);

    //LOGV("%s brightness=%d", __func__, brightness);
    pthread_mutex_lock(&g_lock);
    err = write_int(LCD_BACKLIGHT_FILE, brightness);
    pthread_mutex_unlock(&g_lock);

    return err;
}

static int set_light_battery(struct light_device_t *dev, struct light_state_t const* state) {
    int r, g;

    r = (state->color >> 16) & 0xFF;
    g = (state->color >> 8) & 0xFF;

    write_brightness(LED_RED, r);
    write_brightness(LED_GREEN, g);

    return 0;
}

static int set_light_notifications(struct light_device_t* dev, struct light_state_t const* state){

    if(state->color == 0x00){
        // Off
        //LOGD("set_light_notifications: LED OFF");
        //write_blink_on_off(LED_RED, 0, 0);
        //write_blink_on_off(LED_GREEN, 0, 0);
        write_blink_on_off(LED_BLUE, 0, 0);
    }else if(state->color == 0xffffff){
        // Uknown
        //LOGD("set_light_notifications: LED 0xffffff");
        //write_blink_on_off(LED_RED, 0, 0);
        //write_blink_on_off(LED_GREEN, 0, 0);
        write_blink_on_off(LED_BLUE, 1300, 900);
    }else{
        // Any
        //LOGD("set_light_notifications: LED ANY");
        //write_blink_on_off(LED_RED, 0, 0);
        //write_blink_on_off(LED_GREEN, 0, 0);
        write_blink_on_off(LED_BLUE, 1300, 900);
    }

    return 0;
}

static int close_lights(struct light_device_t *dev) {
    if (dev)
        free(dev);
    return 0;
}

static int open_lights(const struct hw_module_t* module, char const* name, struct hw_device_t** device) {
    int (*set_light)(struct light_device_t* dev, struct light_state_t const *state);
    struct light_device_t *dev;

    if (0 == strcmp(LIGHT_ID_BACKLIGHT, name)) {
        set_light = set_light_backlight;
    }else if (0 == strcmp(LIGHT_ID_BATTERY, name)) {
        set_light = set_light_battery;
    }else if (0 == strcmp(LIGHT_ID_NOTIFICATIONS, name)) {
        set_light = set_light_notifications;
    }else {
        return -EINVAL;
    }

    pthread_once (&g_init, init_globals);
    dev = malloc(sizeof(struct light_device_t));
    memset(dev, 0, sizeof(struct light_device_t));

    dev->common.tag     = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module  = (struct hw_module_t*)module;
    dev->common.close   = (int (*)(struct hw_device_t*))close_lights;
    dev->set_light      = set_light;

    *device = (struct hw_device_t*)dev;
    return 0;
}

static struct hw_module_methods_t lights_module_methods = {
    .open = open_lights,
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag        = HARDWARE_MODULE_TAG,
    .version_major  = 1,
    .version_minor  = 0,
    .id     = LIGHTS_HARDWARE_MODULE_ID,
    .name       = "Ponyo lights module",
    .author     = "Diogo Ferreira <defer@cyanogenmod.com>, Andreas Makris <Andreas.Makris@gmail.com>, devrenax <cm4is01_devrenax@yahoo.co.jp>",
    .methods    = &lights_module_methods,
};

