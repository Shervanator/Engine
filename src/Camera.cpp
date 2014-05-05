#include "Camera.h"
#include <iostream>

Camera::Camera(float fov, float aspect, float zNear, float zFar)
{
  this->projection    = glm::perspective(fov, aspect, zNear, zFar);

  this->direction     = glm::vec3(0, 0, -1);
  this->moveDirection = glm::vec3(0, 0, 0);
  this->velocity      = glm::vec3(0, 0, 0);
}

Camera::~Camera(void)
{
}

glm::mat4 Camera::getViewProjection(void)
{
  return projection * parentNode->getWorldMatrix();
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

void Camera::update(int delta)
{
  if (velocity.x < moveDirection.x) {
    velocity.x += delta * 0.001f;
  } else if (velocity.x > moveDirection.x) {
    velocity.x -= delta * 0.001f;
  }

  if (velocity.y < moveDirection.y) {
    velocity.y += delta * 0.001f;
  } else if (velocity.y > moveDirection.y) {
    velocity.y -= delta * 0.001f;
  }

  if (velocity.z < moveDirection.z) {
    velocity.z += delta * 0.001f;
  } else if (velocity.z > moveDirection.z) {
    velocity.z -= delta * 0.001f;
  }

  // if ((velocity.x < 0.05 && velocity.x > -0.05) && moveDirection.x == 0)
  //   velocity.x = 0;
  // else
  //   position.x += velocity.x;

  // if ((velocity.y < 0.05 && velocity.y > -0.05) && moveDirection.y == 0)
  //   velocity.y = 0;
  // else
  //   position.y += velocity.y;

  // if ((velocity.z < 0.05 && velocity.z > -0.05) && moveDirection.z == 0)
  //   velocity.z = 0;
  // else
  //   position.z += velocity.z;
}
