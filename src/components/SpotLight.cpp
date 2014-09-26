#include "SpotLight.h"

#include "../Engine.h"

SpotLight::SpotLight(glm::vec3 color, float intensity, float cutoff, Attenuation *attenuation) : PointLight(color, intensity, attenuation)
{
  m_cutoff = cutoff;
}

void SpotLight::registerWithEngine(Engine *engine)
{
  engine->getGLManager()->addSpotLight(this);
}

void SpotLight::updateShader(Shader *shader)
{
  shader->updateUniformSpotLight("spotLight", this);
}

float SpotLight::getCutoff(void)
{
  return m_cutoff;
}
