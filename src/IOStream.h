//
//  Author: Shervin Aflatooni
//

#ifndef IO_STREAM
#define IO_STREAM

#include <fstream>

#ifdef ANDROID
  #include "AndroidAssetManager.h"
#endif

enum origin {
  Origin_SET,
  Origin_CUR,
  Origin_END
};

class IOStream
{
public:
  IOStream(const std::string &fileName, const char* pMode);
  ~IOStream(void);

  size_t read(void* pvBuffer, size_t pSize, size_t pCount);
  size_t write(const void* pvBuffer, size_t pSize, size_t pCount);
  bool seek(size_t pOffset, origin pOrigin);
  size_t tell(void) const;
  size_t fileSize(void) const;
  void flush(void);

private:
  size_t m_size;

#ifndef ANDROID
  std::ifstream *m_file;
#else
  AAsset *m_file;
#endif
};

#endif
