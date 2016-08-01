//
//  Author: Shervin Aflatooni
//

#include "Ray.h"

#include <glm/gtx/intersect.hpp>

Ray::Ray(glm::vec3 position, glm::vec3 direction)
{
  m_position = position;
  m_direction = direction;
}

Ray::~Ray(void)
{
}

Ray Ray::getPickRay(glm::vec2 mousePosition, const glm::vec4 &viewport, const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix)
{
  float xRel = mousePosition.x;
  float yRel = viewport.w - mousePosition.y;

  glm::vec3 v1 = glm::unProject(glm::vec3(xRel, yRel, 0.0f), viewMatrix, projectionMatrix, viewport);
  glm::vec3 v2 = glm::unProject(glm::vec3(xRel, yRel, 1.0f), viewMatrix, projectionMatrix, viewport);

  return Ray(v1, glm::normalize(v2 - v1));
}

bool Ray::intersects(const Sphere *sphere, glm::vec3 & intersectionPosition) const
{
  // glm::vec3 intersectionPosition;
  glm::vec3 intersectionNormal;

  return glm::intersectRaySphere(m_position, m_direction, sphere->getParent()->getPosition().xyz(), sphere->getRadius(), intersectionPosition, intersectionNormal);
}

glm::vec3 Ray::getPosition(void) const
{
  return m_position;
}

glm::vec3 Ray::getDirection(void) const
{
  return m_direction;
}

Line Ray::getLine(float length) const
{
  return Line(m_position, m_position + m_direction * length);
}
