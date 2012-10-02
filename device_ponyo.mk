$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)

# The gps config appropriate for this device
$(call inherit-product, device/common/gps/gps_us_supl.mk)

$(call inherit-product-if-exists, vendor/panasonic/ponyo/ponyo-vendor.mk)

DEVICE_PACKAGE_OVERLAYS += device/panasonic/ponyo/overlay

LOCAL_PATH := device/panasonic/ponyo

$(call inherit-product, build/target/product/full.mk)

PRODUCT_BUILD_PROP_OVERRIDES += BUILD_UTC_DATE=0

# proprietary side of the device
$(call inherit-product-if-exists, device/panasonic/ponyo/PonyoProprietary.mk)

# 
PRODUCT_LOCALES := ja_JP

PRODUCT_DEVICE := ponyo
PRODUCT_NAME := cm_ponyo
PRODUCT_BRAND := panasonic
PRODUCT_MODEL := ponyo
PRODUCT_MANUFACTURER := panasonic