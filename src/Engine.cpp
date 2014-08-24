#include "Engine.h"
#include "Logger.h"

#ifdef EMSCRIPTEN
  #include <emscripten.h>

  static Engine *instance = NULL;
#endif


Engine::Engine(Game *game)
{
  log_info("Initializing SDL");
  sdl_manager = new SDLManager(SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  log_info("Initializing GLEW");
  glew_manager = new GLEWManager();

  log_info("Initializing GL");
  gl_manager = new GLManager(sdl_manager->getWidth(), sdl_manager->getHeight());

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
  log_info("Initializing game");
  game->init();

#ifdef EMSCRIPTEN
  instance = this;

  emscripten_set_main_loop(Engine::loop, 0, 1);
#else
  while (!quit) {
    tick();

    SDL_Delay(1);
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
