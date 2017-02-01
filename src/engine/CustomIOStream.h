//
//  Author: Shervin Aflatooni
//

#pragma once

#include "EngineIOStream.h"

#include <assimp/IOStream.hpp>

class CustomIOStream : public Assimp::IOStream
{
  friend class CustomIOSystem;

protected:
  // Constructor protected for private usage by CustomIOSystem
  CustomIOStream(const char* pFile, const char* pMode);

public:
  ~CustomIOStream(void);

  size_t Read(void* pvBuffer, size_t pSize, size_t pCount);
  size_t Write(const void* pvBuffer, size_t pSize, size_t pCount);
  aiReturn Seek(size_t pOffset, aiOrigin pOrigin);
  size_t Tell(void) const;
  size_t FileSize(void) const;
  void Flush(void);

private:
  EngineIOStream *m_iostream;
};
