//
//  Author: Shervin Aflatooni
//

#ifndef WINDOW_H
#define WINDOW_H

#include "settings.h"
#include "Input.h"

#include <string>

#include <glm/glm.hpp>
#include <SDL.h>

// https://stackoverflow.com/questions/4845410/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc
// #undef main

class Window
{
public:
  Window(void);
  ~Window(void);

  void tick(void);
  void swapBuffer(void);
  int poll_event(SDL_Event *event);
  Uint32 getDeltaTime(void);
  Uint32 getFPS(void);

  int getWidth(void);
  int getHeight(void);
  glm::vec4 getViewport(void);

  Input* getInput(void);

  bool shouldQuit(void);

private:
  void logSDLError(const char *msg);

  SDL_Window *win;
  SDL_GLContext glContext;

  Uint32 current_time, old_time, delta_time;

  int width, height;

  Input input;

  bool quit;
};

#endif
