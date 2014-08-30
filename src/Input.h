#ifndef INPUT_H
#define INPUT_H

#include <map>

#include <SDL.h>

class Input
{
public:
  Input(void);
  ~Input(void);

  void handleEvent(SDL_KeyboardEvent keyEvent);
  bool isPressed(SDL_Keycode key);
  bool isReleased(SDL_Keycode key);

private:
  std::map <SDL_Keycode, Uint8> keyState;
};

#endif
