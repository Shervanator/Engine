//
//  Author: Shervin Aflatooni
//

#pragma once

#include "../Component.h"

class FreeLook : public Component
{
public:
  FreeLook(float speed = 1.f);
  ~FreeLook(void);

  virtual void update(Input *input, std::chrono::microseconds delta);

  inline virtual const char *getType(void) { return "FREE_LOOK"; }

private:
  float m_speed;
};
