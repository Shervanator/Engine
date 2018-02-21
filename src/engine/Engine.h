//
//  Author: Shervin Aflatooni
//

#pragma once

#include <chrono>

#include "GLManager.h"
#include "Window.h"
#include "GLEWManager.h"
#include "PhysicsManager.h"

#include "Game.h"

#include "Input.h"
#include "components/Sphere.h"

#define FIXED_TIME_STEP 20

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

  Window *getWindow(void) const;
  GLManager *getGLManager(void) const;
  PhysicsManager *getPhysicsManager(void) const;

  std::chrono::microseconds getDeltaTime(void) const;

private:
  std::unique_ptr<Window> m_window;
  std::unique_ptr<GLEWManager> m_glewManager;
  std::unique_ptr<GLManager> m_glManager;
  std::unique_ptr<PhysicsManager> m_physicsManager;

  std::chrono::high_resolution_clock::time_point m_time, m_lastTime;
  std::chrono::microseconds m_deltaTime;

  Game *game;

  Input input;

  bool quit;
};
