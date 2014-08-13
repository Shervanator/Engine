#include "Engine.h"
#include <iostream>

#ifdef EMSCRIPTEN
  #include <emscripten.h>
#endif

Engine::Engine(int width, int height, Game *game)
{
  sdl_manager = new SDLManager(width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  glew_manager = new GLEWManager();

  gl_manager = new GLManager(width, height);

  this->game = game;

  quit = false;
}

Engine::~Engine(void)
{
  delete sdl_manager;
  delete glew_manager;
  delete gl_manager;
}

void Engine::start(void)
{
  game->init();

#ifdef EMSCRIPTEN
  instance = this;

  emscripten_set_main_loop(Engine::loop, 0, 1);
#else
  while (!quit) {
    tick();
  }
#endif
}

#ifdef EMSCRIPTEN
void Engine::loop(void)
{
  instance->tick();
}
#endif

void Engine::tick(void)
{
  sdl_manager->tick();
  Uint32 delta_time = sdl_manager->getDeltaTime();

  SDL_Event event;
  while (sdl_manager->poll_event(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        keyHandler.handleEvent(event.key);
        break;
      case SDL_QUIT:
        quit = true;
        break;
    }
  }

  game->update(delta_time, &keyHandler);

  game->render(gl_manager);

  sdl_manager->swapBuffer();
}
