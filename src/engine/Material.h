//
//  Author: Shervin Aflatooni
//

#pragma once

#include "Texture.h"

class Material
{
public:
  Material(std::shared_ptr<Texture> diffuseMap, std::shared_ptr<Texture> normalMap = std::make_shared<Texture>(Asset("default_normal.jpg")), std::shared_ptr<Texture> specularMap = std::make_shared<Texture>(Asset("default_specular.jpg")));
  ~Material(void);

  void bind(void) const;

private:
  std::shared_ptr<Texture> m_diffuseMap;
  std::shared_ptr<Texture> m_specularMap;
  std::shared_ptr<Texture> m_normalMap;
};
