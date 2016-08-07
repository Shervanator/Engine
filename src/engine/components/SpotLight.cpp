//
//  Author: Shervin Aflatooni
//

#include "SpotLight.h"

#include "../Engine.h"

SpotLight::SpotLight(glm::vec3 color, float intensity, float cutoff, Attenuation *attenuation) : PointLight(color, intensity, attenuation)
{
  m_cutoff = cutoff;
  m_properties["cutoff"] = Property{FLOAT, &m_cutoff, 0, 10};
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
