//
//  Author: Shervin Aflatooni
//

#ifndef ASSET_H
#define ASSET_H

#include <string>

class Asset
{
public:
  Asset(const std::string &fileName);
  ~Asset(void);

  const char *read(void);
  size_t getSize(void);
  std::string getFileName(void);

private:
  std::string fileName;

  char *buffer;
  size_t size;
};

#endif
