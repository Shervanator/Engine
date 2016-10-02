//
//  Author: Shervin Aflatooni
//

#include "FreeLook.h"

#include "../Logger.h"

FreeLook::FreeLook(float speed)
{
  m_speed = speed;
  horizontal_r=0;
  vertical_r=0;

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
    // FIXME: Dont reset pos to empty quat, maybe set to init rotation
    parentEntity->getTransform().setRotation(glm::quat());
    if (pos.y != 0) {
      vertical_r-=pos.y*m_speed;
      if(vertical_r<-glm::pi<float>()/2)
      vertical_r=-glm::pi<float>()/2;
      if(vertical_r>glm::pi<float>()/2)
      vertical_r=glm::pi<float>()/2;
    }
    if (pos.x != 0) {
      horizontal_r-=pos.x*m_speed;
      while(horizontal_r<-2*glm::pi<float>())
      horizontal_r+=2*glm::pi<float>();
      while(horizontal_r>2*glm::pi<float>())
      horizontal_r-=2*glm::pi<float>();
    }
    parentEntity->getTransform().rotate(glm::vec3(0,1,0),horizontal_r);
    parentEntity->getTransform().rotate(glm::vec3(1,0,0),vertical_r);
#ifdef ANDROID
  } else if (input->mouseIsReleased(SDL_BUTTON_LEFT)) {
#else
  } else if (input->mouseIsReleased(SDL_BUTTON_RIGHT)) {
#endif
    input->releaseMouse();
  }
}
