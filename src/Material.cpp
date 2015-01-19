//
//  Author: Shervin Aflatooni
//

#include "Material.h"

Material::Material(Texture *diffuseMap, Texture *normalMap, Texture *specularMap)
{
  m_diffuseMap  = diffuseMap;
  m_normalMap   = normalMap;
  m_specularMap = specularMap;
}

Material::~Material(void)
{
  delete m_diffuseMap;
  delete m_normalMap;
  delete m_specularMap;
}

void Material::bind(void)
{
  m_diffuseMap->bind(0);
  // if (m_normalMap != NULL)
    m_normalMap->bind(1);
  // if (m_specularMap != NULL)
    m_specularMap->bind(2);
}
