#include "Input.h"

Input::Input(void)
{
}

Input::~Input(void)
{
}

void Input::handleEvent(SDL_KeyboardEvent keyEvent)
{
  keyState[keyEvent.keysym.sym] = keyEvent.state;
  // if (keyEvent.state == SDL_PRESSED) {
  //   std::cout << "KEY: " << keyEvent.keysym.sym << " => pressed" << std::endl;
  // } else if (keyEvent.state == SDL_RELEASED) {
  //   std::cout << "KEY: " << keyEvent.keysym.sym << " => released" << std::endl;
  // }
}

bool Input::isPressed(SDL_Keycode key) {
  return (keyState[key] == SDL_PRESSED);
}

bool Input::isReleased(SDL_Keycode key) {
  return (keyState[key] == SDL_RELEASED);
}
