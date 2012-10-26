## Specify phone tech before including full_phone
$(call inherit-product, vendor/cm/config/gsm.mk)

# Release name
PRODUCT_RELEASE_NAME := pana2_1

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Inherit device configuration
$(call inherit-product, device/panasonic/ponyo/device_ponyo.mk)

## Device identifier. This must come after all inclusions
PRODUCT_DEVICE := ponyo
PRODUCT_NAME := cm_ponyo
PRODUCT_BRAND := docomo
PRODUCT_MODEL := P-01D
PRODUCT_MANUFACTURER := PANASONIC

# Get eng stuff on our userdebug builds
ADDITIONAL_DEFAULT_PROPERTIES += ro.secure=0
ADDITIONAL_DEFAULT_PROPERTIES += ro.allow.mock.location=1