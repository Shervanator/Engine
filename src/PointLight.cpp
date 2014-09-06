#include "PointLight.h"

PointLight::PointLight(glm::vec3 color, float intensity, float range, Attenuation *attenuation) : BaseLight(color, intensity)
{
  m_attenuation = attenuation;
  m_range = range;
}

PointLight::~PointLight(void)
{
  delete m_attenuation;
}

void PointLight::updateShader(Shader *shader)
{
  shader->updateUniformPointLight("pointLight", this);
}

Attenuation *PointLight::getAttenuation(void)
{
  return m_attenuation;
}

float PointLight::getRange(void)
{
  return m_range;
}
