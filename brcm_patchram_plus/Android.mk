ifeq ($(BOARD_HAVE_BLUETOOTH_BCM),false)
LOCAL_PATH:= $(call my-dir)

#
# brcm_patchram_plus.c
#

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES := brcm_patchram_plus.c
LOCAL_MODULE := brcm_patchram_plus
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_MODULE_TAGS := optional

#LOCAL_CFLAGS += -DNEED_BTADDR

include $(BUILD_EXECUTABLE)

endif