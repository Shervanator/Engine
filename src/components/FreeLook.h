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

private:
  float m_speed;
};

#endif
