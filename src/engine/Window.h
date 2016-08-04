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
  Uint32 getDeltaTime(void) const;

  int getWidth(void) const;
  int getHeight(void) const;
  glm::vec4 getViewport(void) const;
  glm::vec2 getDisplaySize(void) const;
  glm::vec2 getDrawableSize(void) const;

  static const char* getClipboardText();
  static void setClipboardText(const char* text);

  void makeCurrentContext(void) const;

  Input* getInput(void);
  SDL_Window* getSDLWindow(void);

  bool shouldQuit(void) const;

  void drawCursor(bool enabled);

private:
  SDL_Window    *m_window;
  SDL_GLContext m_glContext;

  Uint32 m_time, m_lastTime, m_deltaTime;

  int m_width, m_height;

  Input m_input;

  bool m_quit;
};

#endif
