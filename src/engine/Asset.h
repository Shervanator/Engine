//
//  Author: Shervin Aflatooni
//

#pragma once

#include <string>

#include "EngineIOStream.h"

class Asset
{
public:
  Asset(const std::string &fileName);
  ~Asset(void);

  const char *read(void) const;

  EngineIOStream *getIOStream(void) const;

private:
  char *m_buffer;
  EngineIOStream *m_ioStream;
  size_t m_fileSize;
};
