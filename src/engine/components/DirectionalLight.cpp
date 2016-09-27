//
//  Author: Shervin Aflatooni
//

#include "DirectionalLight.h"

#include "../Engine.h"

DirectionalLight::DirectionalLight(glm::vec3 color, float intensity) : BaseLight(color, intensity)
{
}

void DirectionalLight::registerWithEngine(Engine *engine)
{
  engine->getGLManager()->addDirectionalLight(this);
}

void DirectionalLight::deregisterFromEngine(Engine *engine)
{
  engine->getGLManager()->removeDirectionalLight(this);
}

void DirectionalLight::updateShader(Shader *shader)
{
  shader->updateUniformDirectionalLight("directionalLight", this);
}
