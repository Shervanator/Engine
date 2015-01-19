//
//  Author: Shervin Aflatooni
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"

class Material
{
public:
  Material(Texture *diffuseMap, Texture *normalMap = new Texture(Asset("default_normal.jpg")), Texture *specularMap = new Texture(Asset("default_specular.jpg")));
  ~Material(void);

  void bind(void);

private:
  Texture *m_diffuseMap;
  Texture *m_specularMap;
  Texture *m_normalMap;
};

#endif
