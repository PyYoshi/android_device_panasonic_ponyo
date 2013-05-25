# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

############# Prebuilt #############

# Root files
PRODUCT_COPY_FILES += \
	device/panasonic/ponyo/proprietary/root/ueventd.qcom.rc:root/ueventd.qcom.rc \
	device/panasonic/ponyo/proprietary/root/initlogo.rle:root/initlogo.rle \
	device/panasonic/ponyo/proprietary/root/init.qcom.rc:root/init.qcom.rc \
	device/panasonic/ponyo/proprietary/root/init.qcom.sh:root/init.qcom.sh \
	device/panasonic/ponyo/proprietary/root/init.target.rc:root/init.target.rc \
	device/panasonic/ponyo/proprietary/root/init.qcom.usb.rc:root/init.qcom.usb.rc

# Bluetooth firmware and related files
PRODUCT_COPY_FILES += \
	device/panasonic/ponyo/brcm_patchram_plus/BCM4330.hcd:system/etc/BCM4330.hcd \
	device/panasonic/ponyo/prebuilt/init.qcom.bt.sh:system/etc/init.qcom.bt.sh

# Prebuilt files
PRODUCT_COPY_FILES += \
	device/panasonic/ponyo/prebuilt/atmel-touchscreen.idc:system/usr/idc/atmel-touchscreen.idc \
	device/panasonic/ponyo/prebuilt/surf_keypad.kl:system/usr/keylayout/surf_keypad.kl \
	device/panasonic/ponyo/prebuilt/init.qcom.post_boot.sh:system/etc/init.qcom.post_boot.sh \
	device/panasonic/ponyo/prebuilt/init.network_security.sh:system/etc/init.network_security.sh \
	device/panasonic/ponyo/prebuilt/init.gen.nvram.sh:system/etc/init.gen.nvram.sh \
	device/panasonic/ponyo/prebuilt/media_profiles.xml:system/etc/media_profiles.xml

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/handheld_core_hardware.xml:system/etc/permissions/handheld_core_hardware.xml \
    frameworks/native/data/etc/android.hardware.camera.autofocus.xml:system/etc/permissions/android.hardware.camera.autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.flash-autofocus.xml:system/etc/permissions/android.hardware.camera.flash-autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.xml:system/etc/permissions/android.hardware.camera.xml \
    frameworks/native/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
    frameworks/native/data/etc/android.hardware.location.xml:system/etc/permissions/android.hardware.location.xml \
    frameworks/native/data/etc/android.hardware.sensor.accelerometer.xml:system/etc/permissions/android.hardware.sensor.accelerometer.xml \
    frameworks/native/data/etc/android.hardware.sensor.compass.xml:system/etc/permissions/android.hardware.sensor.compass.xml \
    frameworks/native/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/native/data/etc/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
    frameworks/native/data/etc/android.hardware.telephony.gsm.xml:system/etc/permissions/android.hardware.telephony.gsm.xml \
    frameworks/native/data/etc/android.hardware.telephony.cdma.xml:system/etc/permissions/android.hardware.telephony.cdma.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.distinct.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.distinct.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.xml:system/etc/permissions/android.hardware.touchscreen.xml \
    frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
    frameworks/native/data/etc/android.software.sip.voip.xml:system/etc/permissions/android.software.sip.voip.xml \
    frameworks/native/data/etc/android.software.sip.xml:system/etc/permissions/android.software.sip.xml

# Fonts
PRODUCT_COPY_FILES += \
	frameworks/base/data/fonts/MTLc3m.ttf:system/fonts/MTLc3m.ttf \
	frameworks/base/data/fonts/MTLmr3m.ttf:system/fonts/MTLmr3m.ttf

############# Optional files #############

# Audio Libs
PRODUCT_PACKAGES += \
    audio.a2dp.default \
    audio_policy.msm7x30 \
    audio.primary.msm7x30 \
    libaudioutils

# GPS Libs
PRODUCT_PACKAGES += \
    gps.qcom \
    libloc_api-rpc

# HW Libs
PRODUCT_PACKAGES += \
    liboverlay \
    gralloc.msm7x30 \
    copybit.msm7x30 \
    hwcomposer.msm7x30 \
    sensors.qcom \
    lights.default

# OMX Libs
PRODUCT_PACKAGES += \
    libOmxCore \
    libmm-omxcore \
    libOmxVdec \
    libOmxVidEnc \
    libstagefrighthw

# Other Libs and Bins
PRODUCT_PACKAGES += \
    librs_jni \
    brcm_patchram_plus.ponyo \
    hwaddrs

# IME
PRODUCT_PACKAGES += \
    OpenWnn \
    libwnndict \
    libWnnEngDic \
    libWnnJpnDic

# Camera
#PRODUCT_PACKAGES += \
#    Camera \
#    Torch \
#    camera.qcom

# Apps
#PRODUCT_PACKAGES += \

############# Properties #############

# i18n and Timezone
PRODUCT_PROPERTY_OVERRIDES += \
    BUILD_UTC_DATE=0 \
    ro.product.locale.language=ja \
    ro.product.locale.region=JP \
    persist.sys.timezone=Asia/Tokyo

# Wifi
PRODUCT_PROPERTY_OVERRIDES += \
    wifi.interface=wlan0 \
    wifi.supplicant_scan_interval=15

# Graphics
PRODUCT_PROPERTY_OVERRIDES += \
    hwui.render_dirty_regions=false \
    hwui.disable_vsync=true \
    ro.opengles.version=131072 \
    com.qc.hardware=true

# Rild and qcom props
PRODUCT_PROPERTY_OVERRIDES += \
    rild.libpath=/system/lib/libril-qc-qmi-1.so \
    rild.libargs=-d/dev/smd0 \
    ril.subscription.types=NV,RUIM \
    ro.use_data_netmgrd=true \
    ro.multi.rild=true \
    ro.qualcomm.bluetooth.dun=true \
    ro.qualcomm.bluetooth.ftp=true \
    ro.telephony.default_network=0 \
    ro.ril.gprsclass=10 \
    ro.ril.def.agps.mode=2 \
    ro.ril.def.agps.feature=1 \
    ro.telephony.ril.v3=datacall \
    ro.telephony.ril_class=PanasonicQualcommRIL

# USB Mass Storage
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
    persist.sys.usb.config=mass_storage

# system props for SD card emulation of emmc partition
PRODUCT_PROPERTY_OVERRIDES += \
    ro.emmc.sdcard.partition=16
    
# system props for telephony modules
# device supports EHRPD
PRODUCT_PROPERTY_OVERRIDES += \
    ro.config.ehrpd=true

# system props for the cne module
PRODUCT_PROPERTY_OVERRIDES += \
    persist.cne.UseCne=vendor \
    persist.cne.bat.range.low.med=30 \
    persist.cne.bat.range.med.high=60 \
    persist.cne.loc.policy.op=/system/etc/OperatorPolicy.xml \
    persist.cne.loc.policy.user=/system/etc/UserPolicy.xml \
    persist.cne.bwbased.rat.sel=false \
    persist.cne.snsr.based.rat.mgt=false \
    persist.cne.bat.based.rat.mgt=false \
    persist.cne.rat.acq.time.out=30000 \
    persist.cne.rat.acq.retry.tout=0

# BT Mac Adress File
PRODUCT_PROPERTY_OVERRIDES += \
    ro.bt.bdaddr_path=/data/simcom/btadd/bt_add.file

# Chager mode
PRODUCT_PACKAGES += \
	charger \
	charger_res_images

# Other props
PRODUCT_PROPERTY_OVERRIDES += \
    ro.sf.lcd_density=240 \
    ro.com.google.locationfeatures=1 \
    ro.zram.default=0
    ro.com.google.clientidbase=android-pmc
    ro.com.google.clientidbase.ms=android-pmc
    ro.com.google.clientidbase.yt=android-pmc
    ro.com.google.clientidbase.am=android-docomo-jp
    ro.com.google.clientidbase.gmm=android-pmc
