#include "GameManager.h"
#include <iostream>

GameManager::GameManager(void)
{
  quit = false;
}

GameManager::~GameManager(void)
{
}

int GameManager::init(const int width, const int height)
{
  WIDTH = width;
  HEIGHT = height;

  if (sdl_manager.init(width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL) != 0)
    return 1;

  if (glew_manager.init() != 0)
    return 1;

  if (gl_manager.init(width, height) != 0)
    return 1;

  primary_camera = new Camera();

  return 0;
}

void GameManager::tick(void)
{
  sdl_manager.tick();
  Uint32 delta_time = sdl_manager.getDeltaTime();

  SDL_Event event;
  while (sdl_manager.poll_event(&event)) {
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
    primary_camera->moveY(-1.0f);
  }

  if (keyHandler.isPressed(SDLK_DOWN)) {
    primary_camera->moveY(1.0f);
  }

  if (keyHandler.isPressed(SDLK_LEFT)) {
    primary_camera->moveX(1.0f);
  }

  if (keyHandler.isPressed(SDLK_RIGHT)) {
    primary_camera->moveX(-1.0f);
  }

  if (keyHandler.isReleased(SDLK_UP) && keyHandler.isReleased(SDLK_DOWN)) {
    primary_camera->moveY(0.0f);
  }

  if (keyHandler.isReleased(SDLK_LEFT) && keyHandler.isReleased(SDLK_RIGHT)) {
    primary_camera->moveX(0.0f);
  }

  primary_camera->tick(delta_time);
  gl_manager.setLookAt(primary_camera->getPosition(), primary_camera->getDirection(), primary_camera->getUp());
  gl_manager.tick(delta_time);

  sdl_manager.swapBuffer();
}

bool GameManager::shouldQuit(void)
{
  return quit;
}

void GameManager::clean(void)
{
  delete primary_camera;
  sdl_manager.clean();
  glew_manager.clean();
  gl_manager.clean();
}
