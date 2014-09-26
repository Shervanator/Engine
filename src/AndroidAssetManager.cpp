#ifdef ANDROID

#include "AndroidAssetManager.h"

static AAssetManager* NativeAssetManager = 0;

extern "C"
{
   JNIEXPORT void JNICALL Java_org_libsdl_app_SDLActivity_createAssetManager(JNIEnv* env, jclass clazz, jobject assetManager)
   {
      NativeAssetManager = AAssetManager_fromJava(env, assetManager);
   }
};

AAssetManager *AndroidAssetManager::getAssetManager(void)
{
  return NativeAssetManager;
}

#endif
