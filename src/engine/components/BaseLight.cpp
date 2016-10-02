//
//  Author: Shervin Aflatooni
//

#include "BaseLight.h"

BaseLight::BaseLight(glm::vec3 color, float intensity)
{
  m_color = color;
  m_intensity = intensity;

  setProperty("color", COLOR, &m_color.x, 0, 1);
  setProperty("intensity", FLOAT, &m_intensity, 0, 100);
}

BaseLight::~BaseLight(void)
{
}

glm::vec3 BaseLight::getColor(void) const
{
  return m_color;
}

float BaseLight::getIntensity(void) const
{
  return m_intensity;
}
