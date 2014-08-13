#ifndef ENGINE_H
#define ENGINE_H

#include "GLManager.h"
#include "SDLManager.h"
#include "GLEWManager.h"

#include "Game.h"

#include "KeyboardHandler.h"

class Engine
{
public:
  Engine(int width, int height, Game *game);
  ~Engine(void);

#ifdef EMSCRIPTEN
  static Engine *instance;

  static void loop(void);
#endif

  void tick(void);
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
