#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 color, float intensity, float range, float cutoff, Attenuation *attenuation) : PointLight(color, intensity, range, attenuation)
{
  m_cutoff = cutoff;
}

void SpotLight::updateShader(Shader *shader)
{
  shader->updateUniformSpotLight("spotLight", this);
}

float SpotLight::getCutoff(void)
{
  return m_cutoff;
}
