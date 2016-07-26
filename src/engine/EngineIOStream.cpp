//
//  Author: Shervin Aflatooni
//

#include "EngineIOStream.h"

#ifdef EMSCRIPTEN
#elif ANDROID
#else
  #include <whereami.h>
#endif

EngineIOStream::EngineIOStream(const std::string &fileName)
{
  m_fileName = fileName;
#ifdef ANDROID
  m_file = AAssetManager_open(AndroidAssetManager::getAssetManager(), fileName.c_str(), AASSET_MODE_UNKNOWN);
#elif EMSCRIPTEN
  m_file = new std::fstream(ASSET_DIR + fileName, std::ifstream::binary | std::fstream::in | std::fstream::out);
#else
  int length = wai_getExecutablePath(NULL, 0, NULL);
  char *path = new char[length + 1];
  wai_getExecutablePath(path, length, &length);
  path[length] = '\0';
  m_file = new std::fstream((std::string(path) + "/assets/" + fileName).c_str(), std::ifstream::binary | std::fstream::in | std::fstream::out);
#endif
}

EngineIOStream::~EngineIOStream(void)
{
#ifndef ANDROID
  delete m_file;
#else
  AAsset_close(m_file);
#endif
}

size_t EngineIOStream::read(void* pvBuffer, size_t pSize, size_t pCount)
{
#ifndef ANDROID
  m_file->read((char *)pvBuffer, pSize * pCount);
  return m_file->gcount();
#else
  return AAsset_read(m_file, (char *)pvBuffer, pSize * pCount);
#endif
}

size_t EngineIOStream::write(const void* pvBuffer, size_t pSize, size_t pCount)
{
#ifndef ANDROID
  m_file->write((char *)pvBuffer, pSize * pCount);
  return pSize * pCount;
#else
  return 0;
#endif
}

bool EngineIOStream::seek(size_t pOffset, origin pOrigin)
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
  if (!m_file->good()) {
    return false;
  }
#endif

  return true;
}

size_t EngineIOStream::tell(void) const
{
#ifndef ANDROID
  return m_file->tellg();
#else
  return AAsset_getLength(m_file) - AAsset_getRemainingLength(m_file);
#endif
}

size_t EngineIOStream::fileSize(void) const
{
#ifndef ANDROID
  size_t cur = m_file->tellg();
  m_file->seekg(0, std::ios::end);

  size_t end = m_file->tellg();
  m_file->seekg(cur, std::ios::beg);

  return end;
#else
  return AAsset_getLength(m_file);
#endif
}

void EngineIOStream::flush(void)
{
#ifndef ANDROID
  m_file->flush();
#endif
}

std::string EngineIOStream::getFileName(void)
{
  return m_fileName;
}
