//
//  Author: Shervin Aflatooni
//

#pragma once

#include "../Component.h"

class Sphere : public Component, public std::enable_shared_from_this<Sphere>
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
