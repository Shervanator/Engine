//
//  Author: Shervin Aflatooni
//

#include "FreeMove.h"

#include "../Transform.h"

FreeMove::FreeMove(bool moveForwards, float speed)
{
  m_speed = speed;
  m_moveForwards = moveForwards;

  m_properties["speed"].type = FLOAT;
  m_properties["speed"].p = &m_speed;
  m_properties["speed"].min = 0;
  m_properties["speed"].max = 0.1;

  m_properties["forwards"].type = BOOLEAN;
  m_properties["forwards"].p = &m_moveForwards;
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
    if (m_moveForwards) {
      Move(glm::rotate(parentEntity->getTransform().getRotation(), glm::vec3(0.0f, 0.0f, -1.0f)), moveAmount);
    } else {
      Move(glm::rotate(parentEntity->getTransform().getRotation(), glm::vec3(0.0f, 1.0f, 0.0f)), moveAmount);
    }
  }

  if(input->isPressed(SDLK_s)) {
    if (m_moveForwards) {
      Move(glm::rotate(parentEntity->getTransform().getRotation(), glm::vec3(0.0f, 0.0f, 1.0f)), moveAmount);
    } else {
      Move(glm::rotate(parentEntity->getTransform().getRotation(), glm::vec3(0.0f, -1.0f, 0.0f)), moveAmount);
    }
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
