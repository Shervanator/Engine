#include "Camera.h"
#include <iostream>

Camera::Camera(void)
{
  xDelta = 0;
  yDelta = 0;

  horizontalAngle = 0;
  verticalAngle   = 0;

  position      = glm::vec3(0, 0, 30);
  direction     = glm::vec3(0, 0, -1);
  moveDirection = glm::vec3(0, 0, 0);
  velocity      = glm::vec3(0, 0, 0);
  up            = glm::vec3(0, 1, 0);
}

Camera::~Camera(void)
{
}

void Camera::setMousePosition(int xDelta, int yDelta)
{
  this->xDelta = xDelta;
  this->yDelta = yDelta;
}

void Camera::moveX(float x)
{
  moveDirection.x = x;
}

void Camera::moveY(float y)
{
  moveDirection.y = y;
}

void Camera::moveZ(float z)
{
  moveDirection.z = z;
}

void Camera::tick(int delta_time)
{
  if (velocity.x < moveDirection.x) {
    velocity.x += delta_time * 0.001f;
  } else if (velocity.x > moveDirection.x) {
    velocity.x -= delta_time * 0.001f;
  }

  if (velocity.y < moveDirection.y) {
    velocity.y += delta_time * 0.001f;
  } else if (velocity.y > moveDirection.y) {
    velocity.y -= delta_time * 0.001f;
  }

  if (velocity.z < moveDirection.z) {
    velocity.z += delta_time * 0.001f;
  } else if (velocity.z > moveDirection.z) {
    velocity.z -= delta_time * 0.001f;
  }

  if ((velocity.x < 0.05 && velocity.x > -0.05) && moveDirection.x == 0)
    velocity.x = 0;
  else
    position.x += velocity.x;

  if ((velocity.y < 0.05 && velocity.y > -0.05) && moveDirection.y == 0)
    velocity.y = 0;
  else
    position.y += velocity.y;

  if ((velocity.z < 0.05 && velocity.z > -0.05) && moveDirection.z == 0)
    velocity.z = 0;
  else
    position.z += velocity.z;
}

glm::vec3 Camera::getPosition(void)
{
  return position;
}

glm::vec3 Camera::getDirection(void)
{
  return direction + position;
}

glm::vec3 Camera::getUp(void)
{
  return up;
}
