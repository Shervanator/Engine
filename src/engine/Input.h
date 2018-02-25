//
//  Author: Shervin Aflatooni
//

#pragma once

#include <map>
#include <functional>

#include <SDL.h>

#include <glm/glm.hpp>

enum InputEvent {
  IE_PRESSED,
  IE_RELEASED,
  IE_REPEAT
};

class Input
{
public:
  Input(void);
  ~Input(void);

  void handleKeyboardEvent(SDL_KeyboardEvent keyEvent);
  void handleMouseEvent(SDL_MouseButtonEvent buttonEvent);
  void handleMouseWheelEvent(Sint32 x, Sint32 y);
  void handleMultigesture(SDL_MultiGestureEvent multigestureEvent);

  bool isPressed(SDL_Keycode key);
  bool isReleased(SDL_Keycode key);

  bool mouseIsPressed(Uint8 button);
  bool mouseIsReleased(Uint8 button);

  void setMouseDelta(int x, int y);
  void setMousePosition(int x, int y);
  glm::vec2 getMouseDelta(void) const;
  glm::vec2 getMousePosition(void) const;
  glm::vec2 getMouseWheel(void) const;
  SDL_Keymod getKeyModState(void) const;

  void grabMouse(void);
  void releaseMouse(void);

  void bindAction(const std::string &action, InputEvent state, std::function<void(void)> handler);
  void registerKeyToAction(SDL_Keycode key, const std::string &action);
  void registerButtonToAction(Uint8 button, const std::string &action);

private:
  std::map<SDL_Keycode, Uint8> m_keyState;
  std::map<Uint8, Uint8> m_buttonState;
  SDL_Keymod m_keyModState;

  glm::vec2 m_mouseDelta;
  glm::vec2 m_mousePosition;
  glm::vec2 m_mouseWheel;

  std::map<Uint8, std::string> m_buttonToAction;
  std::map<SDL_Keycode, std::string> m_keyToAction;
  std::map<std::string, std::map<InputEvent, std::function<void(void)>>> m_actionInputEventHandler;
};
