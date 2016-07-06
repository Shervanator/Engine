//
//  Author: Shervin Aflatooni
//

#include "Asset.h"

Asset::Asset(const std::string &fileName)
{
  // WTF: for some reason i need to set the name or else exceptions in windows! :(
  m_filename = fileName;
  m_ioStream = new EngineIOStream(fileName);
  m_buffer = new char[m_ioStream->fileSize() + 1];
  m_buffer[m_ioStream->fileSize()] = '\0';
}

Asset::~Asset(void)
{
  delete[] m_buffer;
  delete m_ioStream;
}

const char *Asset::read(void)
{
  m_ioStream->read(m_buffer, sizeof(char), m_ioStream->fileSize());

  return m_buffer;
}

EngineIOStream *Asset::getIOStream(void)
{
  return m_ioStream;
}
