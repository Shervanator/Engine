#ifndef ENGINE_H
#define ENGINE_H

#include "GLManager.h"
#include "Window.h"
#include "GLEWManager.h"
#include "PhysicsManager.h"

#include "Game.h"

#include "Input.h"
#include "Sphere.h"

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

  Window         *getWindow(void);
  GLManager      *getGLManager(void);
  PhysicsManager *getPhysicsManager(void);

private:
  Window         *window;
  GLEWManager    *glew_manager;
  GLManager      *gl_manager;
  PhysicsManager *m_physicsManager;

  Game *game;

  Input input;

  bool quit;
};

#endif
