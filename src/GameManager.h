#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "GLManager.h"
#include "SDLManager.h"
#include "GLEWManager.h"

#include "Game.h"

#include "Camera.h"

#include "KeyboardHandler.h"

class GameManager
{
public:
  GameManager(int width, int height, Game *game);
  ~GameManager(void);

  void start(void);
private:
  SDLManager  *sdl_manager;
  GLEWManager *glew_manager;
  GLManager   *gl_manager;

  Game *game;

  KeyboardHandler keyHandler;

  Camera *primary_camera;

  bool quit;
};

#endif
