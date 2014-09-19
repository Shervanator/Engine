#include "Sphere.h"

Sphere::Sphere(glm::vec3 position, float radius)
{
  m_position = position;
  m_radius = radius;
}

Sphere::~Sphere(void)
{
}

glm::vec3 Sphere::getPosition(void)
{
  return m_position;
}

float Sphere::getRadius(void)
{
  return m_radius;
}
