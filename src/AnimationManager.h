//
//  Author: Shervin Aflatooni
//

#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "components/Animation.h"
#include <vector>

class AnimationManager
{
public:
  AnimationManager(void);
  ~AnimationManager(void);

  void registerAnimation(Animation *animation);

  void update(int delta);

private:
  std::vector<Animation *> m_animations;
  int currentFrame = 0;
};

#endif
