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

glm::mat4 Camera::getViewProjection(void)
{
  return projection * glm::inverse(parentEntity->getWorldMatrix());
}

