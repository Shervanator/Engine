#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"

class Material
{
public:
  Material(Texture *diffuseMap);
  ~Material(void);

  void bind(void);

private:
  Texture *m_diffuseMap;
};

#endif
