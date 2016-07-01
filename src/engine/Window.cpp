//
//  Author: Shervin Aflatooni
//

#include <stdio.h>

#include "Window.h"
#include "Logger.h"

Window::Window(void)
{
  quit = false;

  if (SDL_Init(SDL_INIT_EVERYTHING & ~(SDL_INIT_TIMER | SDL_INIT_HAPTIC)) != 0)
  {
    logSDLError("SDL_Init");
  }

  SDL_DisplayMode mode;
  SDL_GetCurrentDisplayMode(0, &mode);

  this->width = mode.w;
  this->height = mode.h;
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE,    BITS_PER_CHANNEL);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,  BITS_PER_CHANNEL);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,   BITS_PER_CHANNEL);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,  BITS_PER_CHANNEL);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, BITS_PER_CHANNEL * 4);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  BITS_PER_CHANNEL * 2);
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

  // SDL_WINDOW_FULLSCREEN |
  win = SDL_CreateWindow("Engine!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_OPENGL);
  if (win == nullptr)
  {
    logSDLError("SDL_CreateWindow");
  }

  glContext = SDL_GL_CreateContext(win);
  SDL_GL_MakeCurrent(win, glContext);

  current_time = SDL_GetTicks();

  log_info("Window init to: %i x %i", this->width, this->height);
}

Window::~Window(void)
{
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(win);
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
      case SDL_MOUSEMOTION:
        input.setMouseDelta(event.motion.xrel, event.motion.yrel);
        input.setMousePosition(event.motion.x, event.motion.y);
        break;
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        input.handleKeyboardEvent(event.key);
        break;
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        input.handleMouseEvent(event.button);
        break;
      case SDL_QUIT:
        quit = true;
        break;
    }
  }
}

void Window::swapBuffer(void)
{
  SDL_GL_SwapWindow(win);
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

glm::vec4 Window::getViewport(void)
{
  return glm::vec4(0.0f, 0.0f, width, height);
}

bool Window::shouldQuit(void)
{
  return quit;
}
