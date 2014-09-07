#include "PointLight.h"

#include "settings.h"

PointLight::PointLight(glm::vec3 color, float intensity, Attenuation *attenuation) : BaseLight(color, intensity)
{
  m_attenuation = attenuation;

  float a = attenuation->getExponent();
  float b = attenuation->getLinear();
  float c = attenuation->getConstant() - BITS_PER_CHANNEL * getIntensity() * glm::max(color.x, glm::max(color.y, color.z));

  m_range = (-b + glm::sqrt(b * b - 4 * a * c)) / (2 * a);
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
