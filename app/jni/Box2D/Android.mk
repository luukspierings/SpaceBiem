LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Box2D

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/src/*.h) \
	$(wildcard $(LOCAL_PATH)/src/Box2D/Collision/*.h) \
	$(wildcard $(LOCAL_PATH)/src/Box2D/Collision/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/Box2D/Collision/Shapes/*.h) \
	$(wildcard $(LOCAL_PATH)/src/Box2D/Collision/Shapes/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/Box2D/Common/*.h) \
	$(wildcard $(LOCAL_PATH)/src/Box2D/Common/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/Box2D/Dynamics/*.h) \
	$(wildcard $(LOCAL_PATH)/src/Box2D/Dynamics/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/Box2D/Dynamics/Contacts/*.h) \
	$(wildcard $(LOCAL_PATH)/src/Box2D/Dynamics/Contacts/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/Box2D/Dynamics/Joints/*.h) \
	$(wildcard $(LOCAL_PATH)/src/Box2D/Dynamics/Joints/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/Box2D/Rope/*.h) \
	$(wildcard $(LOCAL_PATH)/src/Box2D/Rope/*.cpp))

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES)

include $(BUILD_SHARED_LIBRARY)