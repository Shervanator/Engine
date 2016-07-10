//
//  Author: Shervin Aflatooni
//

#ifndef INPUT_H
#define INPUT_H

#include <map>

#include <SDL.h>

#include <glm/glm.hpp>

class Input
{
public:
  Input(void);
  ~Input(void);

  void handleKeyboardEvent(SDL_KeyboardEvent keyEvent);
  void handleMouseEvent(SDL_MouseButtonEvent buttonEvent);

  bool isPressed(SDL_Keycode key);
  bool isReleased(SDL_Keycode key);
  bool mouseIsPressed(Uint8 button);
  bool mouseIsReleased(Uint8 button);

  void setMouseDelta(int x, int y);
  void setMousePosition(int x, int y);
  glm::vec2 getMouseDelta(void);
  glm::vec2 getMousePosition(void);

  void grabMouse(void);
  void releaseMouse(void);

private:
  std::map <SDL_Keycode, Uint8> keyState;
  std::map <Uint8, Uint8> buttonState;

  glm::vec2 mouseDelta;
  glm::vec2 mousePosition;
};

#endif
