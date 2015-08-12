//
//  Author: Shervin Aflatooni
//

#ifndef ASSET_H
#define ASSET_H

#include <string>

#include "EngineIOStream.h"

class Asset
{
public:
  Asset(const std::string &fileName);
  ~Asset(void);

  const char *read(void);

  EngineIOStream *getIOStream(void);

private:
  char *m_buffer;
  EngineIOStream *m_ioStream;
};

#endif
