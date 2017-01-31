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
  engine->getGLManager()->addDirectionalLight(std::dynamic_pointer_cast<DirectionalLight>(shared_from_this()));
}

void DirectionalLight::deregisterFromEngine(Engine *engine)
{
  engine->getGLManager()->removeDirectionalLight(std::dynamic_pointer_cast<DirectionalLight>(shared_from_this()));
}

void DirectionalLight::updateShader(Shader *shader)
{
  shader->updateUniformDirectionalLight("directionalLight", this);
}
