#include "Input.h"

Input::Input(void)
{
  mouseDelta = glm::vec2(0, 0);
}

Input::~Input(void)
{
}

void Input::handleEvent(SDL_KeyboardEvent keyEvent)
{
  keyState[keyEvent.keysym.sym] = keyEvent.state;
}

bool Input::isPressed(SDL_Keycode key) {
  return (keyState[key] == SDL_PRESSED);
}

bool Input::isReleased(SDL_Keycode key) {
  return (keyState[key] == SDL_RELEASED);
}

void Input::setMouseDelta(int x, int y)
{
  mouseDelta.x = x;
  mouseDelta.y = y;
}

glm::vec2 Input::getMouseDelta(void)
{
  return mouseDelta;
}
