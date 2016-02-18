//
//  Author: Shervin Aflatooni
//

#include "Animation.h"

#include "../Engine.h"
#include "../logger.h"

Animation::~Animation(void)
{
}

void Animation::addPosition(glm::vec3 position)
{
  positions.push_back(position);
}

void Animation::addRotation(glm::quat rotation)
{
  rotations.push_back(rotation);
}

void Animation::addScale(glm::vec3 scale)
{
  scales.push_back(scale);
}

void Animation::update(int delta) {
  if (currentFrame < positions.size())
    getParent()->getTransform().setPosition(positions[currentFrame]);

  if (currentFrame < rotations.size())
    getParent()->getTransform().setRotation(rotations[currentFrame]);
}

void Animation::updateFrameNumber(int frameNumber) {
  previousFrame = currentFrame;
  currentFrame = frameNumber;
}

void Animation::registerWithEngine(Engine *engine)
{
  engine->getAnimationManager()->registerAnimation(this);
}
