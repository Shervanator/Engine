#include "Asset.h"

#include <fstream>

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
    std::ifstream temp(fileName, std::ifstream::binary);

    temp.seekg(0, std::ios::end);
    size = temp.tellg();

    buffer = new char[size + 1];
    buffer[size] = '\0';

    temp.seekg(0);

    temp.read(buffer, size);

    temp.close();
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


// AAsset* file = AAssetManager_open( this->assetManager, fileName.c_str(), AASSET_MODE_BUFFER );
// if (!file)
//   return;
