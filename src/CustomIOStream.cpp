#include "CustomIOStream.h"

#include <string>

CustomIOStream::CustomIOStream(const char* pFile, const char* pMode)
{
  m_file = new std::ifstream("../assets/" + std::string(pFile), std::ifstream::binary);
  m_file->seekg(0, std::ios::end);
  m_size = m_file->tellg();
  m_file->seekg(0);
}

CustomIOStream::~CustomIOStream(void)
{
  delete m_file;
}

size_t CustomIOStream::Read(void* pvBuffer, size_t pSize, size_t pCount)
{
  m_file->read((char *)pvBuffer, pSize * pCount);
  return m_file->gcount() / pSize;
}

size_t CustomIOStream::Write(const void* pvBuffer, size_t pSize, size_t pCount)
{
  return 0;
}

aiReturn CustomIOStream::Seek(size_t pOffset, aiOrigin pOrigin)
{
  switch (pOrigin) {
  case aiOrigin_SET:
    m_file->seekg(pOffset, std::ios::beg);
    break;

  case aiOrigin_CUR:
    m_file->seekg(pOffset, std::ios::cur);
    break;

  case aiOrigin_END:
    m_file->seekg(pOffset, std::ios::end);
    break;
  }

  if (m_file->good()) {
    return AI_SUCCESS;
  } else {
    return AI_FAILURE;
  }
}

size_t CustomIOStream::Tell(void) const
{
  return m_file->tellg();
}

size_t CustomIOStream::FileSize(void) const
{
  return m_size;
}

void CustomIOStream::Flush(void)
{
}

