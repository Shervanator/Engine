LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

LOCAL_CFLAGS := -DGLES2

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
  /usr/local/Cellar/glm/0.9.5.4/include \
  /usr/local/Cellar/assimp/3.0.1270/include

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
  engsrc/Camera.cpp \
  engsrc/Asset.cpp \
  engsrc/Engine.cpp \
  engsrc/GLEWManager.cpp \
  engsrc/GLManager.cpp \
  engsrc/Game.cpp \
  engsrc/GameObject.cpp \
  engsrc/KeyboardHandler.cpp \
  engsrc/Mesh.cpp \
  engsrc/SDLManager.cpp \
  engsrc/SceneNode.cpp \
  engsrc/Shader.cpp \
  engsrc/Texture.cpp \
  engsrc/Transform.cpp \
  engsrc/VisibleObject.cpp \
  engsrc/main.cpp


LOCAL_SHARED_LIBRARIES := SDL2 assimp

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

LOCAL_CPP_FEATURES += exceptions
LOCAL_CFLAGS += -std=c++11

include $(BUILD_SHARED_LIBRARY)
