//
//  Author: Shervin Aflatooni
//

// #define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "Camera.h"

Camera::Camera(float fov, float aspect, float zNear, float zFar)
{
  auto scale = 30.0f;
  auto width = 1920.f * scale;
  auto height = 1080.f * scale;

  this->projection = glm::perspective(fov, aspect, zNear, zFar);
  this->ortho = glm::ortho(-aspect * scale, aspect * scale, -1.0f * scale, 1.0f * scale, 1000.0f, -1000.0f);
}

Camera::~Camera(void)
{
}

glm::mat4 Camera::getOrtho(void)
{
  return ortho;
}

glm::mat4 Camera::getViewMatrix(void)
{
  return glm::inverse(parentEntity->getWorldMatrix());
}

glm::mat4 Camera::getProjectionMatrix(void)
{
  return projection;
}
