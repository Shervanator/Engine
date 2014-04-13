#include "Camera.h"

Camera::Camera(void)
{
  xDelta = 0;
  yDelta = 0;

  horizontalAngle = 0;
  verticalAngle   = 0;

  position = glm::vec3(0, 0, 15);
}

Camera::~Camera(void)
{
}

void Camera::setMousePosition(int xDelta, int yDelta)
{
  this->xDelta = xDelta;
  this->yDelta = yDelta;
}

void Camera::tick(int delta_time, int x, int y)
{
  horizontalAngle += (delta_time / 1000.f) * xDelta;
  verticalAngle   += (delta_time / 1000.f) * yDelta;

  direction = glm::vec3(
    cos(verticalAngle) * sin(horizontalAngle),
    sin(verticalAngle),
    cos(verticalAngle) * cos(horizontalAngle)
  );

  glm::vec3 right = glm::vec3(
    sin(horizontalAngle - 3.14f/2.0f),
    0,
    cos(horizontalAngle - 3.14f/2.0f)
  );

  up = glm::cross( right, direction );

  position += (float)y * direction * (delta_time / 1000.f);
  position += (float)x * right * (delta_time / 1000.f);
}

glm::vec3 Camera::getPosition(void)
{
  return position;
}

glm::vec3 Camera::getDirection(void)
{
  return direction;
}

glm::vec3 Camera::getUp(void)
{
  return up;
}
