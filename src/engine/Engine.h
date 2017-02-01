//
//  Author: Shervin Aflatooni
//

#pragma once

#include "GLManager.h"
#include "Window.h"
#include "GLEWManager.h"
#include "PhysicsManager.h"

#include "Game.h"

#include "Input.h"
#include "components/Sphere.h"

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

  Window         *getWindow(void) const;
  GLManager      *getGLManager(void) const;
  PhysicsManager *getPhysicsManager(void) const;

private:
  std::unique_ptr<Window> m_window;
  std::unique_ptr<GLEWManager> m_glewManager;
  std::unique_ptr<GLManager> m_glManager;
  std::unique_ptr<PhysicsManager> m_physicsManager;

  Game *game;

  Input input;

  bool quit;
};
