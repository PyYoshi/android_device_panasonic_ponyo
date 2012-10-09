$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)

# The gps config appropriate for this device
$(call inherit-product, device/common/gps/gps_us_supl.mk)

$(call inherit-product-if-exists, vendor/panasonic/ponyo/ponyo-vendor.mk)

DEVICE_PACKAGE_OVERLAYS += device/panasonic/ponyo/overlay

LOCAL_PATH := device/panasonic/ponyo

$(call inherit-product, build/target/product/full.mk)

# Additional build prop settings
PRODUCT_PROPERTY_OVERRIDES += \
    BUILD_UTC_DATE=0 \
    ro.dev.dmm=1 \
    dev.dmm.dpd.trigger_delay=30 \
    dev.pm.dyn_samplingrate=1 \
    ro.sf.lcd_density=240 \
    ro.product.locale.language=ja \
    ro.product.locale.region=JP

PRODUCT_PROPERTY_OVERRIDES += \
    rild.libpath=/system/lib/libril-qc-qmi-1.so \
    rild.libargs=-d /dev/smd0 \
    persist.rild.nitz_plmn= \
    persist.rild.nitz_long_ons_0= \
    persist.rild.nitz_long_ons_1= \
    persist.rild.nitz_long_ons_2= \
    persist.rild.nitz_long_ons_3= \
    persist.rild.nitz_short_ons_0= \
    persist.rild.nitz_short_ons_1= \
    persist.rild.nitz_short_ons_2= \
    persist.rild.nitz_short_ons_3= \
    ril.subscription.types=NV,RUIM \
    DEVICE_PROVISIONED=1 \
    debug.sf.hw=1 \
    dev.pm.dyn_samplingrate=1
    ro.build.description=P_01D-user 2.3.4 GRH78 20120627.192518 release-keys \
    ro.build.fingerprint=docomo/P_01D/pana2_1:2.3.4/GRH78/20120627.192518:user/release-keys \
    lpa.decode=true \
    ro.hdmi.enable=true \
    ro.use_data_netmgrd=true \
    ro.emmc.sdcard.partition=16 \
    ro.config.ehrpd=true \
    ro.opengles.version=131072 \
    ro.multi.rild=true


# proprietary side of the device
$(call inherit-product-if-exists, device/panasonic/ponyo/PonyoProprietary.mk)

# 
PRODUCT_LOCALES := ja_JP

PRODUCT_DEVICE := ponyo
PRODUCT_NAME := cm_ponyo
PRODUCT_BRAND := panasonic
PRODUCT_MODEL := ponyo
PRODUCT_MANUFACTURER := panasonic