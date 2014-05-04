#ifndef ENGINE_H
#define ENGINE_H

#include "GLManager.h"
#include "SDLManager.h"
#include "GLEWManager.h"

#include "Game.h"

#include "Camera.h"

#include "KeyboardHandler.h"

class Engine
{
public:
  Engine(int width, int height, Game *game);
  ~Engine(void);

  void start(void);
private:
  SDLManager  *sdl_manager;
  GLEWManager *glew_manager;
  GLManager   *gl_manager;

  Game *game;

  KeyboardHandler keyHandler;

  bool quit;
};

#endif
