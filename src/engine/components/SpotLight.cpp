//
//  Author: Shervin Aflatooni
//

#include "SpotLight.h"

#include "../Engine.h"

SpotLight::SpotLight(glm::vec3 color, float intensity, float cutoff, std::shared_ptr<Attenuation> attenuation) : PointLight(color, intensity, attenuation)
{
  m_cutoff = cutoff;
  setProperty("cutoff", FLOAT, &m_cutoff, 0, 1);
}

void SpotLight::registerWithEngine(Engine *engine)
{
  engine->getGLManager()->addSpotLight(std::dynamic_pointer_cast<SpotLight>(shared_from_this()));
}

void SpotLight::deregisterFromEngine(Engine *engine)
{
  engine->getGLManager()->removeSpotLight(std::dynamic_pointer_cast<SpotLight>(shared_from_this()));
}

void SpotLight::updateShader(Shader *shader)
{
  shader->updateUniformSpotLight("spotLight", this);
}

float SpotLight::getCutoff(void) const
{
  return m_cutoff;
}
