//
//  Author: Shervin Aflatooni
//

#include "CustomIOStream.h"

#include <string>

CustomIOStream::CustomIOStream(const char* pFile, const char* pMode)
{
#ifndef ANDROID
  m_file = new std::ifstream("../assets/" + std::string(pFile), std::ifstream::binary);
  m_file->seekg(0, std::ios::end);
  m_size = m_file->tellg();
  m_file->seekg(0);
#else
  m_file = AAssetManager_open(AndroidAssetManager::getAssetManager(), pFile, AASSET_MODE_UNKNOWN);
  m_size = AAsset_getLength(m_file);
#endif
}

CustomIOStream::~CustomIOStream(void)
{
#ifndef ANDROID
  delete m_file;
#else
  AAsset_close(m_file);
#endif
}

size_t CustomIOStream::Read(void* pvBuffer, size_t pSize, size_t pCount)
{
#ifndef ANDROID
  m_file->read((char *)pvBuffer, pSize * pCount);
  return m_file->gcount() / pSize;
#else
  return AAsset_read(m_file, (char *)pvBuffer, pSize * pCount);
#endif
}

size_t CustomIOStream::Write(const void* pvBuffer, size_t pSize, size_t pCount)
{
  return 0;
}

aiReturn CustomIOStream::Seek(size_t pOffset, aiOrigin pOrigin)
{
  switch (pOrigin) {
  case aiOrigin_SET:
#ifndef ANDROID
    m_file->seekg(pOffset, std::ios::beg);
#else
    AAsset_seek(m_file, pOffset, std::ios::beg);
#endif
    break;

  case aiOrigin_CUR:
#ifndef ANDROID
    m_file->seekg(pOffset, std::ios::cur);
#else
    AAsset_seek(m_file, pOffset, std::ios::cur);
#endif
    break;

  case aiOrigin_END:
#ifndef ANDROID
    m_file->seekg(pOffset, std::ios::end);
#else
    AAsset_seek(m_file, pOffset, std::ios::end);
#endif
    break;

  case _AI_ORIGIN_ENFORCE_ENUM_SIZE:
    return AI_FAILURE;
    break;
  }

#ifndef ANDROID
  if (m_file->good()) {
    return AI_SUCCESS;
  } else {
    return AI_FAILURE;
  }
#else
  return AI_SUCCESS;
#endif
}

size_t CustomIOStream::Tell(void) const
{
#ifndef ANDROID
  return m_file->tellg();
#else
  return m_size - AAsset_getRemainingLength(m_file);
#endif
}

size_t CustomIOStream::FileSize(void) const
{
  return m_size;
}

void CustomIOStream::Flush(void)
{
}
