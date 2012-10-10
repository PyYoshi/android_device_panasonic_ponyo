# inherit from the proprietary version
-include vendor/panasonic/ponyo/BoardConfigVendor.mk

# Call headers from msm-3.0: needed to build libs in hardware/qcom/display
# not work? build/core/binary.mk(489:492)にTARGET_SPECIFIC_HEADER_PATHの定義はされている
TARGET_SPECIFIC_HEADER_PATH := device/panasonic/ponyo/include

#USE_CAMERA_STUB := true

TARGET_BOOTLOADER_BOARD_NAME := ponyo

TARGET_NO_BOOTLOADER := true
TARGET_BOARD_PLATFORM := msm7x30
TARGET_BOARD_PLATFORM_GPU := qcom-adreno200
#TARGET_USES_2G_VM_SPLIT := true
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_ARCH_VARIANT := armv7-a-neon
ARCH_ARM_HAVE_TLS_REGISTER := true
BOARD_HAVE_BLUETOOTH := true
BOARD_USES_QCOM_HARDWARE := true
BOARD_USES_QCOM_GPS := true
BOARD_USES_QCOM_LIBS := true
BOARD_USES_QCOM_LIBRPC := true
BOARD_USE_QCOM_PMEM := true
BOARD_VENDOR_QCOM_AMSS_VERSION := 50000
BOARD_VENDOR_QCOM_GPS_LOC_API_HARDWARE := true
BOARD_VENDOR_QCOM_GPS_LOC_API_AMSS_VERSION := 50000
BOARD_EGL_CFG := device/panasonic/ponyo/prebuilt/egl.cfg
#BOARD_USE_FRAMEBUFFER_ALPHA_CHANNEL := true
BOARD_USE_SCREENCAP := true
#BOARD_OVERLAY_MINIFICATION_LIMIT := 2
#TARGET_GLOBAL_CFLAGS += -mfpu=neon -mfloat-abi=softfp
#TARGET_GLOBAL_CPPFLAGS += -mfpu=neon -mfloat-abi=softfp
COMMON_GLOBAL_CFLAGS += -DQCOM_HARDWARE
#BOARD_OVERLAY_FORMAT_YCbCr_420_SP := true
#TARGET_USES_SF_BYPASS := true
#TARGET_GRALLOC_USES_ASHMEM :=true
#TARGET_USES_OVERLAY := true
USE_OPENGL_RENDERER := true

#
BOARD_CUSTOM_GRAPHICS := ../../../device/panasonic/ponyo/recovery/graphics.c
#BOARD_CUSTOM_RECOVERY_KEYMAPPING:= ../../../device/panasonic/ponyo/recovery/recovery_ui.c
BOARD_CUSTOM_RECOVERY_KEYMAPPING := ../../device/panasonic/ponyo/recovery/recovery_keys.c
RECOVERY_RGBX := true

#
#BOARD_SDCARD_DEVICE_PRIMARY := /dev/block/mmcblk0p1

# Wifi related defines
BOARD_WPA_SUPPLICANT_DRIVER := NL80211
WPA_SUPPLICANT_VERSION      := VER_0_8_X
BOARD_WPA_SUPPLICANT_PRIVATE_LIB := lib_driver_cmd_bcmdhd
BOARD_HOSTAPD_DRIVER        := NL80211
BOARD_HOSTAPD_PRIVATE_LIB   := lib_driver_cmd_bcmdhd
BOARD_WLAN_DEVICE           := bcmdhd
#WIFI_DRIVER_MODULE_PATH     := "/system/lib/modules/dhd.ko"
WIFI_DRIVER_FW_PATH_PARAM   := "/sys/module/bcmdhd/parameters/firmware_path"
WIFI_DRIVER_FW_PATH_STA     := "/vendor/firmware/fw_bcmdhd.bin"
WIFI_DRIVER_FW_PATH_AP      := "/vendor/firmware/fw_bcmdhd_apsta.bin"
WIFI_DRIVER_FW_PATH_P2P     := "/vendor/firmware/fw_bcmdhd_p2p.bin"

BOARD_KERNEL_CMDLINE := console=ttyMSM1 androidboot.hardware=qcom
BOARD_KERNEL_BASE := 0x13800000
BOARD_KERNEL_PAGESIZE := 4096

# fix this up by examining /proc/mtd on a running device
#dev:    size   erasesize  name
#mtd0: 00a00000 00040000 "boot"
#mtd1: 15e00000 00040000 "system"
#mtd2: 0c800000 00040000 "cache"
#mtd3: 00100000 00040000 "misc"
#mtd4: 15480000 00040000 "userdata"
#mtd5: 00300000 00040000 "persist"
#mtd6: 00f00000 00040000 "recovery"
#mtd7: 00f00000 00040000 "recovery_m"
#mtd8: 00280000 00040000 "MIBIB"
#mtd9: 00180000 00040000 "SIM_SECURE"
#mtd10: 000c0000 00040000 "FSBL"
#mtd11: 000c0000 00040000 "FSBL_M"
#mtd12: 001c0000 00040000 "OSBL"
#mtd13: 001c0000 00040000 "OSBL_M"
#mtd14: 01a80000 00040000 "AMSS"
#mtd15: 01a80000 00040000 "AMSS_M"
#mtd16: 00c00000 00040000 "EFS2"
#mtd17: 00140000 00040000 "APPSBL"
#mtd18: 00140000 00040000 "APPSBL_M"
#mtd19: 00080000 00040000 "DSP1"
#mtd20: 00740000 00040000 "QDSP_Q5"
#mtd21: 00540000 00040000 "FOTA"
#mtd22: 06200000 00040000 "APPS"
BOARD_BOOTIMAGE_PARTITION_SIZE := 0x105c0000
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 0x105c0000
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 0x105c0000
BOARD_USERDATAIMAGE_PARTITION_SIZE := 0x105c0000
# HEX(0x00040000) = DEC(262144)
BOARD_FLASH_BLOCK_SIZE := 262144

#TARGET_PREBUILT_KERNEL := device/panasonic/ponyo/zImage
TARGET_KERNEL_SOURCE := kernel/panasonic/ponyo_kernel
TARGET_KERNEL_CONFIG := cyanogenmod_ponyo_defconfig

KERNEL_EXTERNAL_MODULES:
	make -C device/panasonic/ponyo/bcm4330/dhd/linux/ LINUXDIR=$(KERNEL_OUT) ARCH="arm" CROSS_COMPILE="arm-eabi-" dhd-cdc-sdmmc-gpl-debug
	mv device/panasonic/ponyo/bcm4330/dhd/linux/dhd-cdc-sdmmc-gpl-debug-2.6.35.11/dhd.ko $(KERNEL_MODULES_OUT)
TARGET_KERNEL_MODULES := KERNEL_EXTERNAL_MODULES

#BOARD_HAS_NO_SELECT_BUTTON := true
# Use this flag if the board has a ext4 partition larger than 2gb
#BOARD_HAS_LARGE_FILESYSTEM := true
