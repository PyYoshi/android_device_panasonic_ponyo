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
	device/panasonic/ponyo/proprietary/root/init.qcom.rc:root/init.qcom.rc \
	device/panasonic/ponyo/proprietary/root/init.qcom.sh:root/init.qcom.sh \
	device/panasonic/ponyo/proprietary/root/init.rc:root/init.rc \
	device/panasonic/ponyo/proprietary/root/init.target.rc:root/init.target.rc \
	device/panasonic/ponyo/proprietary/root/ueventd.rc:root/ueventd.rc \
	device/panasonic/ponyo/proprietary/root/initlogo.rle:root/initlogo.rle
