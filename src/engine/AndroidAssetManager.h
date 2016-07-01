//
//  Author: Shervin Aflatooni
//

#ifndef ANDROID_ASSET_MANAGER
#define ANDROID_ASSET_MANAGER

#ifdef ANDROID

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class AndroidAssetManager
{
public:
  static AAssetManager *getAssetManager(void);
};

#endif

#endif
