#include <stdio.h>

#include "Window.h"
#include "Logger.h"

Window::Window(void)
{
  quit = false;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    logSDLError("SDL_Init");
  }

#if defined(EMSCRIPTEN)
  this->width = 1200;
  this->height = 800;

  SDL_SetVideoMode(this->width, this->height, 0, SDL_FULLSCREEN | SDL_OPENGL);

  SDL_ShowCursor(0);
  SDL_WM_GrabInput(SDL_GRAB_ON);
#else
  SDL_DisplayMode mode;
  SDL_GetDisplayMode(0, 0, &mode);

  this->width = mode.w;
  this->height = mode.h;
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

  #if defined(GLES3)
    log_info("Using GLES 3");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  #elif defined(GLES2)
    log_info("Using GLES 2");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  #else
    log_info("Using GL 3");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  #endif

  win = SDL_CreateWindow("Engine!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  if (win == nullptr)
  {
    logSDLError("SDL_CreateWindow");
  }

  glContext = SDL_GL_CreateContext(win);
  SDL_GL_MakeCurrent(win, glContext);

  SDL_SetRelativeMouseMode(SDL_TRUE);

  current_time = SDL_GetTicks();
#endif

  log_info("Window init to: %i x %i", this->width, this->height);
}

Window::~Window(void)
{
#if !defined(EMSCRIPTEN)
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(win);
#endif
  SDL_Quit();
}

void Window::logSDLError(const char *msg)
{
  log_err("%s error: %s", msg, SDL_GetError());
}

void Window::tick(void)
{
  old_time     = current_time;
  current_time = SDL_GetTicks();
  delta_time   = current_time - old_time;

  if (current_time % 6 == 0) {
    char buffer[30];
    snprintf(buffer, 30, "FPS: %d, %dms per frame", getFPS(), getDeltaTime() );
    SDL_SetWindowTitle(win, buffer);
  }

  input.setMouseDelta(0, 0);

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        input.handleEvent(event.key);
        break;
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_MOUSEMOTION:
        input.setMouseDelta(event.motion.xrel, event.motion.yrel);
        break;
    }
  }
}

void Window::swapBuffer(void)
{
#if defined(EMSCRIPTEN)
  SDL_GL_SwapBuffers();
#else
  SDL_GL_SwapWindow(win);
#endif
}

Input* Window::getInput(void)
{
  return &input;
}

Uint32 Window::getDeltaTime(void)
{
  return delta_time;
}

Uint32 Window::getFPS(void)
{
  return 1000.0 / delta_time;
}

int Window::getWidth(void)
{
  return width;
}

int Window::getHeight(void)
{
  return height;
}

bool Window::shouldQuit(void)
{
  return quit;
}
