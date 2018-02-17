//
//  Author: Shervin Aflatooni
//

#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
{
  this->m_position = glm::vec4(position, 1);
  this->m_rotation = rotation;
  this->m_scale = scale;
}

Transform::~Transform(void)
{
}

Transform& Transform::rotate(const glm::vec3& axis, float angle)
{
  m_rotation = glm::rotate(m_rotation, angle, axis);
  return *this;
}

Transform& Transform::scale(float scale)
{
  return setScale(getScale() * scale);
}

Transform& Transform::scale(const glm::vec3& scale)
{
  return setScale(getScale() * scale);
}

Transform& Transform::translate(const glm::vec3& position)
{
  return setPosition(m_position.xyz() + position);
}

Transform& Transform::setPosition(const glm::vec3& position)
{
  this->m_position = glm::vec4(position, 1);
  return *this;
}

Transform& Transform::setScale(const glm::vec3& scale)
{
  this->m_scale = scale;
  return *this;
}

Transform& Transform::setRotation(const glm::vec3& axis, float angle)
{
  m_rotation = glm::angleAxis(angle, axis);
  return *this;
}

Transform& Transform::setRotation(const glm::quat& rotation)
{
  this->m_rotation = rotation;
  return *this;
}

glm::vec4 Transform::getPosition(void) const
{
  return m_position;
}

glm::vec3 Transform::getScale(void) const
{
  return m_scale;
}

glm::quat Transform::getRotation(void) const
{
  return m_rotation;
}

glm::mat4 Transform::getTransformMatrix(void) const
{
  return glm::translate(m_position.xyz()) * glm::toMat4(m_rotation) * glm::scale(m_scale);
}

glm::vec4 Transform::getDirection(void) const
{
  return getRotation() * glm::vec4(0, 0, -1, 0);
}
