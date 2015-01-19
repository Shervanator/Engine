//
//  Author: Shervin Aflatooni
//

#include "Asset.h"
#include "Logger.h"

#ifndef ANDROID
  #include <fstream>
#else
  #include "AndroidAssetManager.h"
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
    std::ifstream temp("../assets/" + fileName, std::ifstream::binary);

    temp.seekg(0, std::ios::end);
    size = temp.tellg();

    buffer = new char[size + 1];
    buffer[size] = '\0';

    temp.seekg(0);

    temp.read(buffer, size);

    temp.close();
#else
    AAsset* aAsset = AAssetManager_open(AndroidAssetManager::getAssetManager(), fileName.c_str(), AASSET_MODE_UNKNOWN);

    if(aAsset)
    {
      size = AAsset_getLength(aAsset);


      buffer = new char[size + 1];

      if (int r = AAsset_read(aAsset, buffer, size) < 0)
        log_err("Could not read asset: %i", r);

      buffer[size] = '\0';

      AAsset_close(aAsset);
    } else {
      log_err("Could not read file: %s", fileName.c_str());
    }
#endif
  }

  return buffer;
}

size_t Asset::getSize(void)
{
  return size;
}

std::string Asset::getFileName(void)
{
  return fileName;
}
