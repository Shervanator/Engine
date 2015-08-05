//
//  Author: Shervin Aflatooni
//

#include "IOStream.h"

#include <string>

IOStream::IOStream(const std::string &fileName, const char* pMode)
{
#ifndef ANDROID
  m_file = new std::ifstream("../assets/" + fileName, std::ifstream::binary);
  m_file->seekg(0, std::ios::end);
  m_size = m_file->tellg();
  m_file->seekg(0);
#else
  m_file = AAssetManager_open(AndroidAssetManager::getAssetManager(), fileName.c_str(), AASSET_MODE_UNKNOWN);
  m_size = AAsset_getLength(m_file);
#endif
}

IOStream::~IOStream(void)
{
#ifndef ANDROID
  delete m_file;
#else
  AAsset_close(m_file);
#endif
}

size_t IOStream::read(void* pvBuffer, size_t pSize, size_t pCount)
{
#ifndef ANDROID
  m_file->read((char *)pvBuffer, pSize * pCount);
  return m_file->gcount() / pSize;
#else
  return AAsset_read(m_file, (char *)pvBuffer, pSize * pCount);
#endif
}

size_t IOStream::write(const void* pvBuffer, size_t pSize, size_t pCount)
{
  return 0;
}

bool IOStream::seek(size_t pOffset, origin pOrigin)
{
  switch (pOrigin) {
  case Origin_SET:
#ifndef ANDROID
    m_file->seekg(pOffset, std::ios::beg);
#else
    AAsset_seek(m_file, pOffset, std::ios::beg);
#endif
    break;

  case Origin_CUR:
#ifndef ANDROID
    m_file->seekg(pOffset, std::ios::cur);
#else
    AAsset_seek(m_file, pOffset, std::ios::cur);
#endif
    break;

  case Origin_END:
#ifndef ANDROID
    m_file->seekg(pOffset, std::ios::end);
#else
    AAsset_seek(m_file, pOffset, std::ios::end);
#endif
    break;
  }

#ifndef ANDROID
  if (m_file->good()) {
    return true;
  } else {
    return false;
  }
#else
  return true;
#endif
}

size_t IOStream::tell(void) const
{
#ifndef ANDROID
  return m_file->tellg();
#else
  return m_size - AAsset_getRemainingLength(m_file);
#endif
}

size_t IOStream::fileSize(void) const
{
  return m_size;
}

void IOStream::flush(void)
{
}

