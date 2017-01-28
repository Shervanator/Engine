//
//  Author: Shervin Aflatooni
//

#ifndef SPHERE_H
#define SPHERE_H

#include "../Component.h"

class Sphere : public Component
{
public:
  Sphere(float radius = 0);
  virtual ~Sphere(void);

  virtual void registerWithEngine(Engine *engine);
  virtual void deregisterFromEngine(Engine *engine);

  inline virtual const char *getType(void) { return "SPHERE"; }

  float getRadius(void) const;

private:
  float m_radius;
};

#endif
