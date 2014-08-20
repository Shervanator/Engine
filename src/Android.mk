LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
  /usr/local/Cellar/glm/0.9.5.4/include \
  /usr/local/Cellar/assimp/3.0.1270/include

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
  main.cpp \
  GameObject.cpp \
  Transform.cpp \
  VisibleObject.cpp \
  Game.cpp \
  Camera.cpp \
  GLEWManager.cpp \
  GLManager.cpp \
  Engine.cpp \
  KeyboardHandler.cpp \
  Mesh.cpp \
  SDLManager.cpp \
  SceneNode.cpp \
  Shader.cpp \
  Texture.cpp

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
