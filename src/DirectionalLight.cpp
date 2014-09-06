#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 color, float intensity) : BaseLight(color, intensity)
{
}

void DirectionalLight::updateShader(Shader *shader)
{
  shader->updateUniformDirectionalLight("directionalLight", this);
}
