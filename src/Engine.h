#ifndef ENGINE_H
#define ENGINE_H

#include "GLManager.h"
#include "Window.h"
#include "GLEWManager.h"

#include "Game.h"

#include "Input.h"

class Engine
{
public:
  Engine(Game *game);
  ~Engine(void);

#ifdef EMSCRIPTEN
  static void loop(void);
#endif

  void tick(void);
  void start(void);

  Window *getWindow(void);

private:
  Window      *window;
  GLEWManager *glew_manager;
  GLManager   *gl_manager;

  Game *game;

  Input input;

  bool quit;
};

#endif
