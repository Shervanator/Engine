//
//  Author: Shervin Aflatooni
//

#ifndef FREE_LOOK_H
#define FREE_LOOK_H

#include "../EntityComponent.h"

class FreeLook : public EntityComponent
{
public:
  FreeLook(float speed = 0.001f);
  ~FreeLook(void);

  virtual void updateInput(Input *input, int delta);

  inline virtual const char *getType(void) { return "FREE_LOOK"; }

private:
  float m_speed;
  float horizontal_r;
  float vertical_r;
};

#endif
