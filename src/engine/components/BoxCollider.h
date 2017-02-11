//
//  Author: Shervin Aflatooni
//

#pragma once

#include "BaseCollider.h"

class BoxCollider : public BaseCollider
{
public:
  BoxCollider(const glm::vec3& size, float mass);

  inline virtual const char *getType(void) { return "BOX_COLLIDER"; };
};
