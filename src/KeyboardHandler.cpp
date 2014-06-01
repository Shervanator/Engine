#include "KeyboardHandler.h"

KeyboardHandler::KeyboardHandler(void)
{
}

KeyboardHandler::~KeyboardHandler(void)
{
}

void KeyboardHandler::handleEvent(SDL_KeyboardEvent keyEvent)
{
  keyState[keyEvent.keysym.sym] = keyEvent.state;
  // if (keyEvent.state == SDL_PRESSED) {
  //   std::cout << "KEY: " << keyEvent.keysym.sym << " => pressed" << std::endl;
  // } else if (keyEvent.state == SDL_RELEASED) {
  //   std::cout << "KEY: " << keyEvent.keysym.sym << " => released" << std::endl;
  // }
}

bool KeyboardHandler::isPressed(SDL_Keycode key) {
  return (keyState[key] == SDL_PRESSED);
}

bool KeyboardHandler::isReleased(SDL_Keycode key) {
  return (keyState[key] == SDL_RELEASED);
}
