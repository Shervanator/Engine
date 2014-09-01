#include "Material.h"

Material::Material(Texture *diffuseMap)
{
  m_diffuseMap = diffuseMap;
}

Material::~Material(void)
{
  delete m_diffuseMap;
}

void Material::bind(void)
{
  m_diffuseMap->bind(0);
}
