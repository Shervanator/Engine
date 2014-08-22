#include "Asset.h"
#include "Logger.h"

#ifndef ANDROID
  #include <fstream>
#else
  // for native asset manager
  #include <sys/types.h>
  #include <android/asset_manager.h>
  #include <android/asset_manager_jni.h>
#endif

#ifdef ANDROID
  static AAssetManager* NativeAssetManager = 0;

  extern "C"
  {
     JNIEXPORT void JNICALL Java_org_libsdl_app_SDLActivity_createAssetManager(JNIEnv* env, jclass clazz, jobject assetManager)
     {
        NativeAssetManager = AAssetManager_fromJava(env, assetManager);
     }
  };
#endif

Asset::Asset(const std::string &fileName)
{
  this->fileName = fileName;
  buffer = NULL;
  size = 0;
}

Asset::~Asset(void)
{
  delete buffer;
}

const char *Asset::read(void)
{
  if (!buffer) {
    log_info("Reading file: %s from disk", fileName.c_str());
#ifndef ANDROID
    std::ifstream temp(fileName, std::ifstream::binary);

    temp.seekg(0, std::ios::end);
    size = temp.tellg();

    buffer = new char[size + 1];
    buffer[size] = '\0';

    temp.seekg(0);

    temp.read(buffer, size);

    temp.close();
#else
    AAsset* aAsset = AAssetManager_open(NativeAssetManager, fileName.c_str(), AASSET_MODE_BUFFER);

    if(aAsset)
    {
      size = AAsset_getLength(aAsset);

      // AAsset_read(aAsset, buffer, size);
      const void* pData = AAsset_getBuffer(aAsset);
      buffer = new char[size + 1];
      memcpy( buffer, pData, size * sizeof( char ) );
      buffer[size] = '\0';

      AAsset_close(aAsset);
    } else {
      log_err("Could not read file: %s", fileName.c_str());
    }
#endif
  }

  return buffer;
}

int Asset::getSize(void)
{
  return size;
}

std::string Asset::getFileName(void)
{
  return fileName;
}
