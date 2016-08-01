//
//  Author: Shervin Aflatooni
//

#include "Input.h"

Input::Input(void)
{
  mouseDelta = glm::vec2(0, 0);
  mousePosition = glm::vec2(0, 0);
}

Input::~Input(void)
{
}

void Input::handleKeyboardEvent(SDL_KeyboardEvent keyEvent)
{
  keyState[keyEvent.keysym.sym] = keyEvent.state;
}

void Input::handleMouseEvent(SDL_MouseButtonEvent buttonEvent)
{
  buttonState[buttonEvent.button] = buttonEvent.state;
}

bool Input::isPressed(SDL_Keycode key) const
{
  return (keyState.at(key) == SDL_PRESSED);
}

bool Input::isReleased(SDL_Keycode key) const
{
  return (keyState.at(key) == SDL_RELEASED);
}

bool Input::mouseIsPressed(Uint8 button) const
{
  return (buttonState.at(button) == SDL_PRESSED);
}

bool Input::mouseIsReleased(Uint8 button) const
{
  return (buttonState.at(button) == SDL_RELEASED);
}

void Input::setMouseDelta(int x, int y)
{
  mouseDelta.x = x;
  mouseDelta.y = y;
}

void Input::setMousePosition(int x, int y)
{
  mousePosition.x = x;
  mousePosition.y = y;
}

glm::vec2 Input::getMouseDelta(void) const
{
  return mouseDelta;
}

glm::vec2 Input::getMousePosition(void) const
{
  return mousePosition;
}

void Input::grabMouse(void)
{
  SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Input::releaseMouse(void)
{
  SDL_SetRelativeMouseMode(SDL_FALSE);
}
