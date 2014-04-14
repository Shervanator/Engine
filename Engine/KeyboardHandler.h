#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#include <map>

#ifdef _WIN32
  #include <SDL.h>
#else
  #include <SDL2/SDL.h>
#endif

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
