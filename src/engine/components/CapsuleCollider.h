//
//  Author: Shervin Aflatooni
//

#pragma once

#include "BaseCollider.h"

class CapsuleCollider : public BaseCollider
{
public:
  CapsuleCollider(float radius, float height, float mass);

  inline virtual const char *getType(void) { return "CAPSULE_COLLIDER"; };
};
