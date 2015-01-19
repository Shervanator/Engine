//
//  Author: Shervin Aflatooni
//

#include "FreeLook.h"

#include "../Logger.h"

FreeLook::FreeLook(float speed)
{
  m_speed = speed;
}

FreeLook::~FreeLook(void)
{
}

void FreeLook::updateInput(Input *input, int delta)
{
  if (input->mouseIsPressed(SDL_BUTTON_RIGHT)) {
    input->grabMouse();
    glm::vec2 pos = input->getMouseDelta();
    if (pos.y != 0) {
      parentEntity->getTransform().rotate(glm::vec3(1, 0, 0), -pos.y * m_speed);
    }
    if (pos.x != 0) {
      parentEntity->getTransform().rotate(glm::vec3(0, 1, 0), -pos.x * m_speed);
    }
  } else if (input->mouseIsReleased(SDL_BUTTON_RIGHT)) {
    input->releaseMouse();
  }
}
