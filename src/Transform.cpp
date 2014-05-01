#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
{
  this->position = position;
  this->rotation = rotation;
  this->scale = scale;
}

Transform::~Transform(void)
{
}

void Transform::setPosition(const glm::vec3& position)
{
  this->position = position;
}

void Transform::setScale(const glm::vec3& scale)
{
  this->scale = scale;
}

void Transform::setRotation(const glm::vec3& axis, float angle)
{
  rotation = glm::angleAxis(glm::degrees(angle), axis);
}

void Transform::setRotation(const glm::quat& rotation)
{
  this->rotation = rotation;
}

glm::vec3 Transform::getPosition(void)
{
  return position;
}

glm::vec3 Transform::getScale(void)
{
  return scale;
}

glm::quat Transform::getRotation(void)
{
  return rotation;
}

glm::mat4 Transform::getTransformMatrix(void)
{
  return glm::translate(position) * glm::toMat4(rotation) * glm::scale(scale);
}
