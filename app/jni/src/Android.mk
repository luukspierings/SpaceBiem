LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/../SDL2_image

# Add your application source files here...
LOCAL_SRC_FILES := main.cpp \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/components/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/core/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/devices/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/devices/audio/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/devices/graphics/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/entities/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/managers/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/primitives/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/scenes/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/systems/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/systems/physics/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/components/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/core/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/devices/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/entities/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/managers/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/primitives/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/scenes/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/biemgine/systems/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/builder/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/components/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/entities/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/factories/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/globals/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/scenes/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/systems/*.cpp) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/builder/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/components/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/entities/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/factories/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/globals/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/scenes/*.h) \
    $(wildcard $(LOCAL_PATH)/spacebiem/spacebiem/systems/*.h)

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf SDL2_mixer SDL2_image Box2D

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
