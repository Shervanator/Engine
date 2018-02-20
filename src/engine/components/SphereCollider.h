//
//  Author: Shervin Aflatooni
//

#pragma once

#include "BaseCollider.h"

class SphereCollider : public BaseCollider
{
public:
  SphereCollider(float size, float mass);

  inline virtual const char *getType(void) { return "SPHERE_COLLIDER"; };
};
