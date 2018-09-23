LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES:= stormmx.c
LOCAL_MODULE := stormmxgpio
include $(BUILD_EXECUTABLE)
