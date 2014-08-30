LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := assimp
LOCAL_SRC_FILES := libassimp.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := main

LOCAL_CFLAGS := -DGLES2

SDL_PATH := ../SDL

# TODO: FIX ABSOLUTE PATHS
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
  /usr/local/Cellar/glm/0.9.5.4/include \
  /Users/shervinaflatooni/Git/assimp/include

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
  engsrc/Camera.cpp \
  engsrc/Asset.cpp \
  engsrc/Engine.cpp \
  engsrc/GLEWManager.cpp \
  engsrc/GLManager.cpp \
  engsrc/Game.cpp \
  engsrc/EntityComponent.cpp \
  engsrc/KeyboardHandler.cpp \
  engsrc/Mesh.cpp \
  engsrc/SDLManager.cpp \
  engsrc/Entity.cpp \
  engsrc/Shader.cpp \
  engsrc/Texture.cpp \
  engsrc/Transform.cpp \
  engsrc/MeshRenderer.cpp \
  engsrc/main.cpp

LOCAL_SHARED_LIBRARIES := SDL2 assimp

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog -landroid

LOCAL_CPP_FEATURES += exceptions
LOCAL_CFLAGS += -std=c++11

include $(BUILD_SHARED_LIBRARY)
