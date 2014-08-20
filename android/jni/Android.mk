include $(call all-subdir-makefiles)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES := /usr/local/Cellar/assimp/3.0.1270/include
LOCAL_MODULE := assimp
LOCAL_SRC_FILES := libassimp.so
include $(PREBUILT_SHARED_LIBRARY)
