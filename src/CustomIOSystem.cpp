#include "CustomIOSystem.h"

#include "CustomIOStream.h"

#include <string>
#include <stdio.h>
#include <unistd.h>

CustomIOSystem::CustomIOSystem(void)
{
}
CustomIOSystem::~CustomIOSystem(void)
{
}

bool CustomIOSystem::ComparePaths (const char *one, const char *second) const
{
  if (strcmp(one, second) == 0) {
    return true;
  } else {
    return false;
  }
}

bool CustomIOSystem::Exists(const char* pFile) const
{
  if(access(("../assets/" + std::string(pFile)).c_str(), F_OK) != -1) {
    return true;
  } else {
    return false;
  }
}

char CustomIOSystem::getOsSeparator(void) const
{
  return '/';
}

Assimp::IOStream *CustomIOSystem::Open(const char* pFile, const char* pMode)
{
  return new CustomIOStream(pFile, pMode);
}

void CustomIOSystem::Close(Assimp::IOStream* pFile)
{
  delete pFile;
}
