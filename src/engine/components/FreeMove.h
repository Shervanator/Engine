//
//  Author: Shervin Aflatooni
//

#pragma once

#include "../Component.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class FreeMove : public Component
{
public:
  FreeMove(bool moveForwards = true, float speed = 10.f);
  ~FreeMove(void);

  virtual void update(Input *input, std::chrono::microseconds delta);

  inline virtual const char *getType(void) { return "FREE_MOVE"; }

private:
  void Move(const glm::vec3 &direction, float amount);

  float m_speed;
  bool m_moveForwards;
};
