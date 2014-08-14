#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#include <map>

#include <SDL.h>

class KeyboardHandler
{
public:
  KeyboardHandler(void);
  ~KeyboardHandler(void);

  void handleEvent(SDL_KeyboardEvent keyEvent);
  bool isPressed(SDL_Keycode key);
  bool isReleased(SDL_Keycode key);

private:
  std::map <SDL_Keycode, Uint8> keyState;
};

#endif
