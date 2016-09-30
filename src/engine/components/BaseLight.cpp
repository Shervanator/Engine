//
//  Author: Shervin Aflatooni
//

#include "BaseLight.h"

BaseLight::BaseLight(glm::vec3 color, float intensity)
{
  m_color = color;
  m_intensity = intensity;

  m_properties["color"] = (Property){COLOR, &m_color.x, 0, 1};
  m_properties["intensity"] = (Property){FLOAT, &m_intensity, 0, 100};
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
