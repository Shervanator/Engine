#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"

class Material
{
public:
  Material(Texture *diffuseMap, Texture *normalMap = NULL, Texture *specularMap = NULL);
  ~Material(void);

  void bind(void);

private:
  Texture *m_diffuseMap;
  Texture *m_specularMap;
  Texture *m_normalMap;
};

#endif
