//
//  Author: Shervin Aflatooni
//

#include "BaseLight.h"

BaseLight::BaseLight(glm::vec3 color, float intensity)
{
  m_color = color;
  m_intensity = intensity;

  m_properties["color"].type = COLOR;
  m_properties["color"].p = &m_color.x;
  m_properties["color"].min = 0;
  m_properties["color"].max = 1;

  m_properties["intensity"].type = FLOAT;
  m_properties["intensity"].p = &m_intensity;
  m_properties["intensity"].min = 0;
  m_properties["intensity"].max = 100;
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
