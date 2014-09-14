#ifndef CUSTOM_IO_STREAM
#define CUSTOM_IO_STREAM

#include <fstream>

#ifdef ANDROID
  #include "AndroidAssetManager.h"
#endif

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
#ifndef ANDROID
  std::ifstream *m_file;
#else
  AAsset *m_file;
#endif
  size_t m_size;
};

#endif
