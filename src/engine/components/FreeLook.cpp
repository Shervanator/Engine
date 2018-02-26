//
//  Author: Shervin Aflatooni
//

#include "FreeLook.h"
#include "../Engine.h"

FreeLook::FreeLook(float speed)
{
  m_speed = speed;
  m_look = false;

  setProperty("speed", FLOAT, &m_speed, 0, 5);
  setProperty("look", BOOLEAN, &m_look);
}

FreeLook::~FreeLook(void)
{
}

void FreeLook::registerWithEngine(Engine *engine)
{
  auto input = engine->getWindow()->getInput();
  input->registerButtonToAction(SDL_BUTTON_RIGHT, "look");

  input->bindAction("look", IE_PRESSED, [this]() {
    m_look = true;
});
  input->bindAction("look", IE_RELEASED, [this]() {
    m_look = false;
  });
}

void FreeLook::deregisterFromEngine(Engine *engine)
{
  auto input = engine->getWindow()->getInput();
  input->unbindAction("look");
}

void FreeLook::update(Input *input, std::chrono::microseconds delta)
{
  float moveAmount = m_speed * std::chrono::duration_cast<std::chrono::duration<float>>(delta).count();

  if (m_look)
  {
    input->grabMouse();
    glm::vec2 pos = input->getMouseDelta();
    if (pos.y != 0)
    {
      m_parentEntity->getTransform().rotate(glm::vec3(1, 0, 0), -pos.y * moveAmount);
    }
    if (pos.x != 0)
    {
      m_parentEntity->getTransform().setRotation(glm::angleAxis(-pos.x * moveAmount, glm::vec3(0, 1, 0)) * m_parentEntity->getTransform().getRotation());
    }
  }
  else {
    input->releaseMouse();
  }
}
