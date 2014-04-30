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

void Transform::setPosition(float x, float y, float z)
{
  position.x = x;
  position.y = y;
  position.z = z;
}

void Transform::setRotation(float x, float y, float z, float w)
{
  rotation.x = x;
  rotation.y = y;
  rotation.z = z;
  rotation.w = w;
}

glm::mat4 Transform::getTransformMatrix(void)
{
  return glm::translate(position) * glm::toMat4(rotation) * glm::scale(scale);
}
