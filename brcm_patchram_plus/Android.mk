LOCAL_PATH:= $(call my-dir)

#
# brcm_patchram_plus.c
#

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES := brcm_patchram_plus.c
LOCAL_MODULE := brcm_patchram_plus.dat
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_MODULE_TAGS := optional

#Add by Taoyuan for BCM4330 bluetooth address 2011.5.3
ifeq ($(BOARD_HAVE_BLUETOOTH_BCM4330_BTADDR),true)
  LOCAL_CFLAGS += -DNEED_BTADDR
endif

include $(BUILD_EXECUTABLE)

