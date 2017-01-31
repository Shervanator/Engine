//
//  Author: Shervin Aflatooni
//

#include "Material.h"

Material::Material(std::shared_ptr<Texture> diffuseMap, std::shared_ptr<Texture> normalMap, std::shared_ptr<Texture> specularMap)
{
  m_diffuseMap  = diffuseMap;
  m_normalMap   = normalMap;
  m_specularMap = specularMap;
}

Material::~Material(void)
{
}

void Material::bind(void) const
{
  m_diffuseMap->bind(0);
  // if (m_normalMap != NULL)
    m_normalMap->bind(1);
  // if (m_specularMap != NULL)
    m_specularMap->bind(2);
}
