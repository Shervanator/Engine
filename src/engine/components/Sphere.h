//
//  Author: Shervin Aflatooni
//

#ifndef SPHERE_H
#define SPHERE_H

#include "../EntityComponent.h"

class Sphere : public EntityComponent
{
public:
  Sphere(float radius = 0);
  virtual ~Sphere(void);

  virtual void registerWithEngine(Engine *engine);
  virtual void deregisterFromEngine(Engine *engine);

  float getRadius(void) const;

private:
  float m_radius;
};

#endif
