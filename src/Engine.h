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

  void projectLine(glm::vec3* v1, glm::vec3* v2, glm::vec2 mousePosition, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
  Window      *window;
  GLEWManager *glew_manager;
  GLManager   *gl_manager;

  Game *game;

  Input input;

  bool quit;
};

#endif
