//
//  Author: Shervin Aflatooni
//

#include "PointLight.h"

#include "../Engine.h"
#include "../settings.h"

PointLight::PointLight(glm::vec3 color, float intensity, Attenuation *attenuation) : BaseLight(color, intensity)
{
  m_attenuation = attenuation;

  // float a = attenuation->getExponent();
  // float b = attenuation->getLinear();
  // float c = attenuation->getConstant() - BITS_PER_CHANNEL * getIntensity() * glm::max(color.x, glm::max(color.y, color.z));

  m_properties["exp"] = (Property){FLOAT, &m_attenuation->m_exponent, 0, 0.5};
  m_properties["linear"] = (Property){FLOAT, &m_attenuation->m_linear, 0, 1};
  m_properties["const"] = (Property){FLOAT, &m_attenuation->m_constant, 0, 1};

  // m_range = (-b + glm::sqrt(b * b - 4 * a * c)) / (2 * a);
}

PointLight::~PointLight(void)
{
  delete m_attenuation;
}

void PointLight::registerWithEngine(Engine *engine)
{
  engine->getGLManager()->addPointLight(this);
}

void PointLight::deregisterFromEngine(Engine *engine)
{
  engine->getGLManager()->removePointLight(this);
}

void PointLight::updateShader(Shader *shader)
{
  shader->updateUniformPointLight("pointLight", this);
}

Attenuation *PointLight::getAttenuation(void) const
{
  return m_attenuation;
}

float PointLight::getRange(void)
{
  float a = m_attenuation->getExponent();
  float b = m_attenuation->getLinear();
  float c = m_attenuation->getConstant() - BITS_PER_CHANNEL * getIntensity() * glm::max(m_color.x, glm::max(m_color.y, m_color.z));

  m_range = (-b + glm::sqrt(b * b - 4 * a * c)) / (2 * a);
  return m_range;
}
