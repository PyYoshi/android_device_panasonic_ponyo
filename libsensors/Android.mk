# Copyright (C) 2008 The Android Open Source Project
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

LOCAL_PATH := $(call my-dir)

################### sensors.default.so ###################
# HAL module implemenation, not prelinked, and stored in
# hw/<SENSORS_HARDWARE_MODULE_ID>.<ro.product.board>.so
include $(CLEAR_VARS)
LOCAL_MODULE := sensors.qcom
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS := -DLOG_TAG=\"Sensors\"
LOCAL_SRC_FILES := \
   sensors.c
LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)

##################### cm3623_ps_test_0 #####################
include $(CLEAR_VARS)
LOCAL_SRC_FILES := cm3623_ps_test_0.c
LOCAL_MODULE := cm3623_ps_test_0
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

##################### cm3623_als_test_0 #####################
include $(CLEAR_VARS)
LOCAL_SRC_FILES := cm3623_als_test_0.c
LOCAL_MODULE := cm3623_als_test_0
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

##################### ecompass_test #####################
include $(CLEAR_VARS)
LOCAL_SRC_FILES := ecompass_test.c
LOCAL_MODULE := ecompass_test
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)