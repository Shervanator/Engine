//
//  Author: Shervin Aflatooni
//

#pragma once

#include "../Component.h"

class FreeLook : public Component
{
public:
  FreeLook(float speed = 0.001f);
  ~FreeLook(void);

  virtual void updateInput(Input *input, int delta);

  inline virtual const char *getType(void) { return "FREE_LOOK"; }

private:
  float m_speed;
};
