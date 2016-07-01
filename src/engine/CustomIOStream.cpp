//
//  Author: Shervin Aflatooni
//

#include "CustomIOStream.h"

#include <string>

CustomIOStream::CustomIOStream(const char* pFile, const char* pMode)
{
  m_iostream = new EngineIOStream(std::string(pFile));
}

CustomIOStream::~CustomIOStream(void)
{
  delete m_iostream;
}

size_t CustomIOStream::Read(void* pvBuffer, size_t pSize, size_t pCount)
{
  return m_iostream->read(pvBuffer, pSize, pCount);
}

size_t CustomIOStream::Write(const void* pvBuffer, size_t pSize, size_t pCount)
{
  return m_iostream->write(pvBuffer, pSize, pCount);
}

aiReturn CustomIOStream::Seek(size_t pOffset, aiOrigin pOrigin)
{
  switch (pOrigin) {
  case aiOrigin_SET:
    return m_iostream->seek(pOffset, Origin_SET) ? AI_SUCCESS : AI_FAILURE;
    break;

  case aiOrigin_CUR:
    return m_iostream->seek(pOffset, Origin_CUR) ? AI_SUCCESS : AI_FAILURE;
    break;

  case aiOrigin_END:
    return m_iostream->seek(pOffset, Origin_END) ? AI_SUCCESS : AI_FAILURE;
    break;
  }
}

size_t CustomIOStream::Tell(void) const
{
  return m_iostream->tell();
}

size_t CustomIOStream::FileSize(void) const
{
  return m_iostream->fileSize();
}

void CustomIOStream::Flush(void)
{
  m_iostream->flush();
}
