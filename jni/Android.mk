LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

OPENCV_CAMERA_MODULES:=on
OPENCV_INSTALL_MODULES:=on

include $(OPENCV_SDK)/sdk/native/jni/OpenCV.mk

LOCAL_MODULE    := MyOpenCVSkeleton
LOCAL_SRC_FILES := native.cpp
LOCAL_LDLIBS    += -lm -llog -landroid

include $(BUILD_SHARED_LIBRARY)
