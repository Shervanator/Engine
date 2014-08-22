#ifndef ASSET_H
#define ASSET_H

#include <string>

class Asset
{
public:
  Asset(const std::string &fileName);
  ~Asset(void);

  const char *read(void);
  int getSize(void);
  std::string getFileName(void);

private:
  std::string fileName;

  char *buffer;
  int size;
};

#endif
