$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)

# The gps config appropriate for this device
$(call inherit-product, device/common/gps/gps_as_supl.mk)

$(call inherit-product, frameworks/native/build/phone-hdpi-512-dalvik-heap.mk) 

$(call inherit-product-if-exists, vendor/panasonic/ponyo/ponyo-vendor.mk)

DEVICE_PACKAGE_OVERLAYS += device/panasonic/ponyo/overlay

LOCAL_PATH := device/panasonic/ponyo

$(call inherit-product, build/target/product/full.mk)

# proprietary side of the device
$(call inherit-product-if-exists, device/panasonic/ponyo/PonyoProprietary.mk)

# P-01D
#ro.build.description=P_01D-user 2.3.4 GRH78 20120627.192518 release-keys
#ro.build.fingerprint=docomo/P_01D/pana2_1:2.3.4/GRH78/20120627.192518:user/release-keys
# SO-03D
#ro.build.description=SO-03D-user 4.0.4 6.1.F.0.106 lb9-zw test-keys
#ro.build.fingerprint=docomo/SO-03D_1256-7200/SO-03D:4.0.4/6.1.F.0.106/lb9-zw:user/release-keys

PRODUCT_BUILD_PROP_OVERRIDES += PRODUCT_NAME=P_01D BUILD_FINGERPRINT=docomo/P_01D/pana2_1:2.3.4/GRH78/20120627.192518:user/release-keys PRIVATE_BUILD_DESC="P_01D-user 2.3.4 GRH78 20120627.192518 release-keys"

# high-density artwork where available
PRODUCT_AAPT_CONFIG := normal hdpi
PRODUCT_AAPT_PREF_CONFIG := hdpi

PRODUCT_DEVICE := ponyo
PRODUCT_NAME := cm_ponyo
PRODUCT_BRAND := docomo
PRODUCT_MODEL := P-01D
PRODUCT_MANUFACTURER := PANASONIC

$(call inherit-product, build/target/product/full_base_telephony.mk)
