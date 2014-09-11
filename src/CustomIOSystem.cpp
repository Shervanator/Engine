#include "CustomIOSystem.h"

#include "CustomIOStream.h"

CustomIOSystem::CustomIOSystem(void)
{
}
CustomIOSystem::~CustomIOSystem(void)
{
}

bool CustomIOSystem::ComparePaths (const char *one, const char *second) const
{
  return false;
}

bool CustomIOSystem::Exists(const char* pFile) const
{
  return false;
}

char CustomIOSystem::GetOsSeparator(void) const
{
  return '/';
}

Assimp::IOStream *CustomIOSystem::Open(const char* pFile, const char* pMode)
{
  return new CustomIOStream();
}

void CustomIOSystem::Close(Assimp::IOStream* pFile)
{
  delete pFile;
}
