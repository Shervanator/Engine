#include "Camera.h"

glm::mat4 Camera::getViewMatrix(void) const
{
  return glm::inverse(parentEntity->getWorldMatrix());
}

glm::mat4 Camera::getProjectionMatrix(void) const
{
  return projection;
}
