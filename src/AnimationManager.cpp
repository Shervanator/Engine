//
//  Author: Shervin Aflatooni
//

#include "AnimationManager.h"

AnimationManager::AnimationManager(void)
{
}

AnimationManager::~AnimationManager(void)
{
}

void AnimationManager::update(int delta)
{
  for (auto animation : m_animations) {
    animation->updateFrameNumber(currentFrame);
  }
  currentFrame++;
}

void AnimationManager::registerAnimation(Animation *animation) {
  m_animations.push_back(animation);
}
