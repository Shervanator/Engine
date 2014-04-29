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

glm::mat4 Transform::getTransform(void)
{
  return glm::translate(position) * glm::toMat4(rotation) * glm::scale(scale);
}
