//
//  Author: Shervin Aflatooni
//

#include <stdio.h>

#include "Window.h"
#include "Logger.h"

Window::Window(void)
{
  m_quit = false;

  if (SDL_Init(SDL_INIT_EVERYTHING & ~(SDL_INIT_TIMER | SDL_INIT_HAPTIC)) != 0)
  {
    log_err("SDL_Init error: %s", SDL_GetError());
  }

  SDL_DisplayMode mode;
  SDL_GetCurrentDisplayMode(0, &mode);

  this->m_width = mode.w;
  this->m_height = mode.h;
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
  m_window = SDL_CreateWindow("Engine!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->m_width, this->m_height, SDL_WINDOW_OPENGL);
  if (m_window == nullptr)
  {
    log_err("SDL_CreateWindow error: %s", SDL_GetError());
  }

  m_glContext = SDL_GL_CreateContext(m_window);
  if (m_glContext == nullptr) {
    log_err("SDL_GL_CreateContext error: %s", SDL_GetError());
  }

  SDL_GL_SetSwapInterval(0);

  current_time = SDL_GetTicks();

  log_info("Window init to: %i x %i", this->m_width, this->m_height);
}

Window::~Window(void)
{
  SDL_GL_DeleteContext(m_glContext);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Window::tick(void)
{
  old_time     = current_time;
  current_time = SDL_GetTicks();
  delta_time   = current_time - old_time;

  if (current_time % 6 == 0) {
    // char buffer[30];
    // TODO: FIX THIS IN WINDOWS
    //log_info("fps: %d", getFPS());
    //snprintf(buffer, 30, "FPS: %d, %dms per frame", getFPS(), getDeltaTime() );
    //SDL_SetWindowTitle(m_window, buffer);
  }

  m_input.setMouseDelta(0, 0);

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_MOUSEMOTION:
        m_input.setMouseDelta(event.motion.xrel, event.motion.yrel);
        m_input.setMousePosition(event.motion.x, event.motion.y);
        break;
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        m_input.handleKeyboardEvent(event.key);
        break;
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        m_input.handleMouseEvent(event.button);
        break;
      case SDL_QUIT:
        m_quit = true;
        break;
    }
  }
}

void Window::swapBuffer(void)
{
  SDL_GL_SwapWindow(m_window);
}

Input* Window::getInput(void)
{
  return &m_input;
}

Uint32 Window::getDeltaTime(void) const
{
  return delta_time;
}

Uint32 Window::getFPS(void) const
{
  return 1000.0 / delta_time;
}

int Window::getWidth(void) const
{
  return this->m_width;
}

int Window::getHeight(void) const
{
  return this->m_height;
}

glm::vec4 Window::getViewport(void) const
{
  return glm::vec4(0.0f, 0.0f, this->m_width, this->m_height);
}

void Window::makeCurrentContext(void) const
{
  SDL_GL_MakeCurrent(m_window, m_glContext);
}

bool Window::shouldQuit(void) const
{
  return m_quit;
}
