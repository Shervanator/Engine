//
//  Author: Shervin Aflatooni
//

#include "Input.h"

Input::Input(void)
{
  m_mouseDelta = glm::vec2(0, 0);
  m_mousePosition = glm::vec2(0, 0);
}

Input::~Input(void)
{
}

void Input::handleKeyboardEvent(SDL_KeyboardEvent keyEvent)
{
  m_keyState[keyEvent.keysym.sym] = keyEvent.state;
}

void Input::handleMouseEvent(SDL_MouseButtonEvent buttonEvent)
{
  m_buttonState[buttonEvent.button] = buttonEvent.state;
}

bool Input::isPressed(SDL_Keycode key)
{
  return (m_keyState[key] == SDL_PRESSED);
}

bool Input::isReleased(SDL_Keycode key)
{
  return (m_keyState[key] == SDL_RELEASED);
}

bool Input::mouseIsPressed(Uint8 button)
{
  return (m_buttonState[button] == SDL_PRESSED);
}

bool Input::mouseIsReleased(Uint8 button)
{
  return (m_buttonState[button] == SDL_RELEASED);
}

void Input::setMouseDelta(int x, int y)
{
  m_mouseDelta.x = x;
  m_mouseDelta.y = y;
}

void Input::setMousePosition(int x, int y)
{
  m_mousePosition.x = x;
  m_mousePosition.y = y;
}

glm::vec2 Input::getMouseDelta(void) const
{
  return m_mouseDelta;
}

glm::vec2 Input::getMousePosition(void) const
{
  return m_mousePosition;
}

void Input::grabMouse(void)
{
  SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Input::releaseMouse(void)
{
  SDL_SetRelativeMouseMode(SDL_FALSE);
}
