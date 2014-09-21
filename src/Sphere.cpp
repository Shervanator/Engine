#include "Sphere.h"

Sphere::Sphere(float radius)
{
  m_radius = radius;
}

Sphere::~Sphere(void)
{
}

float Sphere::getRadius(void)
{
  return m_radius;
}
