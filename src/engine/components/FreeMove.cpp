//
//  Author: Shervin Aflatooni
//

#include "FreeMove.h"

#include "../Transform.h"

FreeMove::FreeMove(bool moveForwards, float speed)
{
  m_speed = speed;
  m_moveForwards = moveForwards;

  m_properties["speed"] = Property{FLOAT, &m_speed, 0, 0.1};
  m_properties["forwards"] = Property{BOOLEAN, &m_moveForwards};
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
