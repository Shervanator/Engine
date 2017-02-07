//
//  Author: Shervin Aflatooni
//

#include "FreeLook.h"

FreeLook::FreeLook(float speed)
{
  m_speed = speed;
  setProperty("speed", FLOAT, &m_speed, 0, 0.01);
}

FreeLook::~FreeLook(void)
{
}

void FreeLook::updateInput(Input *input, int delta)
{
#ifdef ANDROID
  if (input->mouseIsPressed(SDL_BUTTON_LEFT)) {
#else
  if (input->mouseIsPressed(SDL_BUTTON_RIGHT)) {
#endif
    input->grabMouse();
    glm::vec2 pos = input->getMouseDelta();
    if (pos.y != 0) {
      m_parentEntity->getTransform().rotate(glm::vec3(1, 0, 0), -pos.y * m_speed);
    }
    if (pos.x != 0) {
      m_parentEntity->getTransform().setRotation(glm::angleAxis(-pos.x * m_speed, glm::vec3(0, 1, 0)) * m_parentEntity->getTransform().getRotation());
    }
#ifdef ANDROID
  } else if (input->mouseIsReleased(SDL_BUTTON_LEFT)) {
#else
  } else if (input->mouseIsReleased(SDL_BUTTON_RIGHT)) {
#endif
    input->releaseMouse();
  }
}
