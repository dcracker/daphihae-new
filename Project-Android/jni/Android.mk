LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
# Here we give our module name and source file(s)
LOCAL_DEFAULT_CPP_EXTENSION := cpp
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog -landroid -lEGL -lGLESv1_CM 
LOCAL_MODULE := nativeImpl

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../MultiPlatformFramework/Android
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../MultiPlatformFramework
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../OpenGLFramework
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../DaPhiHaeGame
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Libs/glm

FILE_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../MultiPlatformFramework/Android/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../MultiPlatformFramework/Common/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../OpenGLFramework/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../DaPhiHaeGame/*.cpp)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_STATIC_LIBRARIES := png
#LOCAL_CPPFLAGS  := -std=c++11

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, ../libs/)
$(call import-module, libpng)
# $(LOCAL_BUILT_MODULE) : post_build

#post_build :
#	@echo Hi, I'm post-build.
#	cp D:/MyDocument/Project/DaPhiHae/Resources/test.png D:/MyDocument/Project/DaPhiHae/Project-Android/assets