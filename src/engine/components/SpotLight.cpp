//
//  Author: Shervin Aflatooni
//

#include "SpotLight.h"

#include "../Engine.h"

SpotLight::SpotLight(glm::vec3 color, float intensity, float cutoff, Attenuation *attenuation) : PointLight(color, intensity, attenuation)
{
  m_cutoff = cutoff;
  m_properties["cutoff"].type = FLOAT;
  m_properties["cutoff"].p = &m_cutoff;
  m_properties["cutoff"].min = 0;
  m_properties["cutoff"].max = 1;
}

void SpotLight::registerWithEngine(Engine *engine)
{
  engine->getGLManager()->addSpotLight(this);
}

void SpotLight::deregisterFromEngine(Engine *engine)
{
  engine->getGLManager()->removeSpotLight(this);
}

void SpotLight::updateShader(Shader *shader)
{
  shader->updateUniformSpotLight("spotLight", this);
}

float SpotLight::getCutoff(void) const
{
  return m_cutoff;
}
