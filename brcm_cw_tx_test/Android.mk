LOCAL_PATH:= $(call my-dir)

#
# brcm_cw_tx_test.c
#

include $(CLEAR_VARS)

LOCAL_SRC_FILES := brcm_cw_tx_test.c
LOCAL_MODULE := brcm_cw_tx_test
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)
