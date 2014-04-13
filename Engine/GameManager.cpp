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
  Uint32 delta_time = sdl_manager.getDeltaTime();

  SDL_Event event;
  while (sdl_manager.poll_event(&event)) {
    if (event.type == SDL_MOUSEMOTION) {
      std::cout << "x: " << event.motion.xrel << " :: y: " << event.motion.yrel << std::endl;
      primary_camera->setMousePosition(event.motion.xrel, event.motion.yrel);
      primary_camera->tick(delta_time);
    } else if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_UP) {
        primary_camera->tick(delta_time, 0, 1);
      } else if (event.key.keysym.sym == SDLK_DOWN) {
        primary_camera->tick(delta_time, 0, -1);
      } else if (event.key.keysym.sym == SDLK_LEFT) {
        primary_camera->tick(delta_time, -1, 0);
      } else if (event.key.keysym.sym == SDLK_RIGHT) {
        primary_camera->tick(delta_time, 1, 0);
      }
    } else if (event.type == SDL_QUIT) {
      quit = true;
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
      // glUseProgram(shader2->getProgram());
    }
  }

  gl_manager.setLookAt(primary_camera->getPosition(), primary_camera->getDirection(), primary_camera->getUp());
  gl_manager.tick(delta_time);
  sdl_manager.tick();
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
