#ifndef SPHERE_H
#define SPHERE_H

#include "EntityComponent.h"

class Sphere : public EntityComponent
{
public:
  Sphere(float radius = 0);
  ~Sphere(void);

  float getRadius(void);

private:
  float m_radius;
};

#endif
