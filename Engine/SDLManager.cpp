#include <iostream>
#include <stdio.h>

#include "SDLManager.h"

SDLManager::SDLManager(void)
{
}

SDLManager::~SDLManager(void)
{
}

void SDLManager::clean(void)
{
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(win);
  SDL_Quit();
}

int SDLManager::init(const int width, const int height, Uint32 flags)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    logSDLError("SDL_Init");
    return 1;
  }
  
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
  if (win == nullptr)
  {
    logSDLError("SDL_CreateWindow");
    return 1;
  }

  glContext = SDL_GL_CreateContext(win);

  // SDL_SetRelativeMouseMode(SDL_TRUE);

  current_time = SDL_GetTicks();

  return 0;
}

void SDLManager::logSDLError(const std::string &msg)
{
  std::cout << msg << " error: " << SDL_GetError() << std::endl;
}

void SDLManager::tick(void)
{
  old_time     = current_time;
  current_time = SDL_GetTicks();
  delta_time   = current_time - old_time;

  if (current_time % 6 == 0) {
    char buffer[30];
    snprintf(buffer, 30, "FPS: %d, %dms per frame", getFPS(), getDeltaTime() );
    SDL_SetWindowTitle(win, buffer);
  }
}

void SDLManager::swapBuffer(void)
{
  SDL_GL_SwapWindow(win);
}

int SDLManager::poll_event(SDL_Event *event)
{
  return SDL_PollEvent(event);
}

Uint32 SDLManager::getDeltaTime(void)
{
  return delta_time;
}

Uint32 SDLManager::getFPS(void)
{
  return 1000.0 / delta_time;
}