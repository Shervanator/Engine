#include "Engine.h"
#include <iostream>

Engine::Engine(int width, int height, Game *game)
{
  sdl_manager = new SDLManager(width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  glew_manager = new GLEWManager();

  gl_manager = new GLManager(width, height);

  primary_camera = new Camera(glm::vec3(0, 0, 10), 45.0f, width / (float)height, 0.1f, 100.0f);

  this->game = game;

  quit = false;
}

Engine::~Engine(void)
{
  delete primary_camera;
  delete sdl_manager;
  delete glew_manager;
  delete gl_manager;
}

void Engine::start(void)
{
  game->init();

  while (!quit)
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

    if (keyHandler.isPressed(SDLK_UP)) {
      primary_camera->moveY(1.0f);
    }

    if (keyHandler.isPressed(SDLK_DOWN)) {
      primary_camera->moveY(-1.0f);
    }

    if (keyHandler.isPressed(SDLK_LEFT)) {
      primary_camera->moveX(-1.0f);
    }

    if (keyHandler.isPressed(SDLK_RIGHT)) {
      primary_camera->moveX(1.0f);
    }

    if (keyHandler.isReleased(SDLK_UP) && keyHandler.isReleased(SDLK_DOWN)) {
      primary_camera->moveY(0.0f);
    }

    if (keyHandler.isReleased(SDLK_LEFT) && keyHandler.isReleased(SDLK_RIGHT)) {
      primary_camera->moveX(0.0f);
    }

    primary_camera->tick(delta_time);

    gl_manager->setViewProjection(primary_camera->getViewProjection());

    game->update(delta_time);

    game->render(gl_manager);

    sdl_manager->swapBuffer();
  }
}
