#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
{
  this->m_position = position;
  this->m_rotation = rotation;
  this->m_scale = scale;
}

Transform::~Transform(void)
{
}

void Transform::rotate(const glm::vec3& axis, float angle)
{
  m_rotation = glm::rotate(m_rotation, angle, axis);
}

void Transform::scale(float scale)
{
  setScale(getScale() * scale);
}

void Transform::scale(const glm::vec3& scale)
{
  setScale(getScale() * scale);
}

void Transform::translate(const glm::vec3& position)
{
  setPosition(getPosition() + position);
}

void Transform::setPosition(const glm::vec3& position)
{
  this->m_position = position;
}

void Transform::setScale(const glm::vec3& scale)
{
  this->m_scale = scale;
}

void Transform::setRotation(const glm::vec3& axis, float angle)
{
  m_rotation = glm::angleAxis(angle, axis);
}

void Transform::setRotation(const glm::quat& rotation)
{
  this->m_rotation = rotation;
}

glm::vec3& Transform::getPosition(void)
{
  return m_position;
}

glm::vec3 Transform::getScale(void)
{
  return m_scale;
}

glm::quat Transform::getRotation(void)
{
  return m_rotation;
}

glm::mat4 Transform::getTransformMatrix(void)
{
  return glm::translate(m_position) * glm::toMat4(m_rotation) * glm::scale(m_scale);
}
