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

# Prebuilt libraries that are needed to build open-source libraries

PRODUCT_COPY_FILES += \
	device/panasonic/ponyo/proprietary/root/ueventd.qcom.rc:root/ueventd.qcom.rc \
	device/panasonic/ponyo/proprietary/root/initlogo.rle:root/initlogo.rle \
	device/panasonic/ponyo/proprietary/root/init.qcom.rc:root/init.qcom.rc \
	device/panasonic/ponyo/proprietary/root/init.qcom.sh:root/init.qcom.sh \
	device/panasonic/ponyo/proprietary/root/init.target.rc:root/init.target.rc \
	device/panasonic/ponyo/prebuilt/atmel-touchscreen.idc:system/usr/idc/atmel-touchscreen.idc \
	device/panasonic/ponyo/proprietary/root/init.qcom.usb.rc:root/init.qcom.usb.rc

PRODUCT_COPY_FILES += \
	device/panasonic/ponyo/brcm_patchram_plus/BCM4330.hcd:system/etc/BCM4330.hcd \
	device/panasonic/ponyo/brcm_patchram_plus/init.qcom.btcit.sh:system/etc/init.qcom.btcit.sh \
	device/panasonic/ponyo/brcm_patchram_plus/btparam.sh:system/etc/btparam.sh \
	device/panasonic/ponyo/brcm_patchram_plus/TEST_ONLY_Ponyo_FixedAFHMap_384M_20110511.hcd:system/etc/TEST_ONLY_Ponyo_FixedAFHMap_384M_20110511.hcd

PRODUCT_COPY_FILES += \
	device/panasonic/ponyo/prebuilt/surf_keypad.kl:system/usr/keylayout/surf_keypad.kl

PRODUCT_COPY_FILES += \
    frameworks/base/data/etc/handheld_core_hardware.xml:system/etc/permissions/handheld_core_hardware.xml \
    frameworks/base/data/etc/android.hardware.camera.autofocus.xml:system/etc/permissions/android.hardware.camera.autofocus.xml \
    frameworks/base/data/etc/android.hardware.camera.flash-autofocus.xml:system/etc/permissions/android.hardware.camera.flash-autofocus.xml \
    frameworks/base/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
    frameworks/base/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
    frameworks/base/data/etc/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
    frameworks/base/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/base/data/etc/android.hardware.touchscreen.xml:system/etc/permissions/android.hardware.touchscreen.xml \
    frameworks/base/data/etc/android.hardware.touchscreen.multitouch.distinct.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.distinct.xml \
    frameworks/base/data/etc/android.hardware.usb.accessory.xml:system/etc/permissions/android.hardware.usb.accessory.xml \
    frameworks/base/data/etc/android.software.sip.voip.xml:system/etc/permissions/android.software.sip.voip.xml \
    frameworks/base/data/etc/android.hardware.telephony.gsm.xml:system/etc/permissions/android.hardware.telephony.gsm.xml

PRODUCT_PACKAGES += \
    librs_jn \
    overlay.default \
    gralloc.msm7x30 \
    copybit.msm7x30 \
    hwcomposer.msm7x30 \
    lights.default \
    gps.qcom \
    libloc_api-rpc \
    libOmxCore \
    libmm-omxcore \
    libOmxVdec \
    libOmxVidEnc \
    libstagefrighthw \
    audio.a2dp.default \
    audio_policy.msm7x30 \
    libaudioutils

PRODUCT_COPY_FILES += \
	frameworks/base/data/fonts/MTLc3m.ttf:system/fonts/MTLc3m.ttf \
	frameworks/base/data/fonts/MTLmr3m.ttf:system/fonts/MTLmr3m.ttf

PRODUCT_PROPERTY_OVERRIDES += \
    hwui.render_dirty_regions=false \
    hwui.disable_vsync=true \
    ro.opengles.version=131072 \
    ro.sf.lcd_density=240 \
    ro.product.locale.language=ja \
    ro.product.locale.region=JP

PRODUCT_PROPERTY_OVERRIDES += \
    BUILD_UTC_DATE=0 \
    ro.dev.dmm=1 \
    dev.dmm.dpd.trigger_delay=30 \
    dev.pm.dyn_samplingrate=1 \
    rild.libpath=/system/lib/libril-qc-qmi-1.so \
    rild.libargs=-d /dev/smd0 \
    ril.subscription.types=NV,RUIM \
    ro.hdmi.enable=true

PRODUCT_PROPERTY_OVERRIDES += \
    gsm.version.baseband=07.0109.0068




