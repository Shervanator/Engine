#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "Camera.h"

Camera::Camera(float fov, float aspect, float zNear, float zFar)
{
  this->projection = glm::perspective(fov, aspect, zNear, zFar);
}

Camera::~Camera(void)
{
}

glm::mat4 Camera::getViewMatrix(void)
{
  return glm::inverse(parentEntity->getWorldMatrix());
}

glm::mat4 Camera::getProjectionMatrix(void)
{
  return projection;
}

