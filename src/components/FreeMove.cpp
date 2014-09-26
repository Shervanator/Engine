#include "FreeMove.h"

#include "../Transform.h"

FreeMove::FreeMove(float speed)
{
  m_speed = speed;
}

FreeMove::~FreeMove(void)
{
}

void FreeMove::updateInput(Input *input, int delta)
{
  float moveAmount = m_speed * delta;

  if(input->isPressed(SDLK_LSHIFT)) {
    moveAmount *= 4.0f;
  }

  if(input->isPressed(SDLK_w)) {
    Move(glm::rotate(parentEntity->getTransform().getRotation(), glm::vec3(0.0f, 0.0f, -1.0f)), moveAmount);
  }

  if(input->isPressed(SDLK_s)) {
    Move(glm::rotate(parentEntity->getTransform().getRotation(), glm::vec3(0.0f, 0.0f, 1.0f)), moveAmount);
  }

  if(input->isPressed(SDLK_a)) {
    Move(glm::rotate(parentEntity->getTransform().getRotation(), glm::vec3(-1.0f, 0.0f, 0.0f)), moveAmount);
  }

  if(input->isPressed(SDLK_d)) {
    Move(glm::rotate(parentEntity->getTransform().getRotation(), glm::vec3(1.0f, 0.0f, 0.0f)), moveAmount);
  }
}

void FreeMove::Move(const glm::vec3& direction, float amount)
{
  parentEntity->getTransform().translate(direction * amount);
}
