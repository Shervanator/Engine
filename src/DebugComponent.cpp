#include "DebugComponent.h"

DebugComponent::DebugComponent(void)
{
  box = new Box();
}

DebugComponent::~DebugComponent(void)
{
  delete box;
}

void DebugComponent::render(Shader *shader)
{
  shader->bind();
  glUniformMatrix4fv(shader->getUniformLocation("Model", 1), 1, GL_FALSE, &(parentEntity->getWorldMatrix())[0][0]);

  box->render();
}
