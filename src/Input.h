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

  void handleEvent(SDL_KeyboardEvent keyEvent);
  bool isPressed(SDL_Keycode key);
  bool isReleased(SDL_Keycode key);
  void setMouseDelta(int x, int y);
  glm::vec2 getMouseDelta(void);

private:
  std::map <SDL_Keycode, Uint8> keyState;

  glm::vec2 mouseDelta;
};

#endif
