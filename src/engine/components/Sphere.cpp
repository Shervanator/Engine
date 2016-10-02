//
//  Author: Shervin Aflatooni
//

#include "Sphere.h"

#include "../Engine.h"

Sphere::Sphere(float radius)
{
  m_radius = radius;
  m_properties["radius"].type = FLOAT;
  m_properties["radius"].p = &m_radius;
  m_properties["radius"].min = 0;
  m_properties["radius"].max = 10;
}

Sphere::~Sphere(void)
{
}

void Sphere::registerWithEngine(Engine *engine)
{
  engine->getPhysicsManager()->registerCollider(this);
}

void Sphere::deregisterFromEngine(Engine *engine)
{
  engine->getPhysicsManager()->deregisterCollider(this);
}

float Sphere::getRadius(void) const
{
  return m_radius;
}
