#include "Engine.h"
#include "Logger.h"
#include "Ray.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#ifdef EMSCRIPTEN
  #include <emscripten.h>

  static Engine *instance = NULL;
#endif


Engine::Engine(Game *game)
{
  log_info("Initializing SDL");
  window = new Window();

  log_info("Initializing GLEW");
  glew_manager = new GLEWManager();

  log_info("Initializing GL");
  gl_manager = new GLManager(window->getWidth(), window->getHeight());

  this->game = game;

  quit = false;
}

Engine::~Engine(void)
{
  delete window;
  delete glew_manager;
  delete gl_manager;
}

void Engine::start(void)
{
  game->setEngine(this);

  log_info("Initializing game");
  game->init(gl_manager);

#ifdef EMSCRIPTEN
  instance = this;

  emscripten_set_main_loop(Engine::loop, 0, 1);
#else
  while (!quit) {
    tick();

    SDL_Delay(1);
  }
#endif
}

#ifdef EMSCRIPTEN
void Engine::loop(void)
{
  instance->tick();
}
#endif

void Engine::tick(void)
{
  window->tick();
  Uint32 delta_time = window->getDeltaTime();

  quit = window->shouldQuit();

  game->updateInput(window->getInput(), delta_time);

  game->update(delta_time);

  game->render(gl_manager);

  if (window->getInput()->mouseIsPressed(SDL_BUTTON_LEFT)) {
    glm::vec4 viewport = glm::vec4(0.0f, 0.0f, window->getWidth(), window->getHeight());
    Ray ray = Ray::getPickRay(window->getInput()->getMousePosition(), viewport, gl_manager->getViewMatrix(), gl_manager->getProjectionMatrix());

    gl_manager->drawLine(ray.getPosition(), ray.getPosition() + (ray.getDirection()) * 100.0f);
  }

  window->swapBuffer();
}

Window *Engine::getWindow(void)
{
  return window;
}
