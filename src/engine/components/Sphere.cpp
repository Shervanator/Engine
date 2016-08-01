//
//  Author: Shervin Aflatooni
//

#include "Sphere.h"

#include "../Engine.h"

Sphere::Sphere(float radius)
{
  m_radius = radius;
}

Sphere::~Sphere(void)
{
}

void Sphere::registerWithEngine(Engine *engine)
{
  engine->getPhysicsManager()->registerCollider(this);
}

float Sphere::getRadius(void) const
{
  return m_radius;
}
