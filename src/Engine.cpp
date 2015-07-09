//
//  Author: Shervin Aflatooni
//

#include "Engine.h"
#include "Logger.h"
#include "Ray.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <limits>

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

  log_info("Initializing Physics Manager");
  m_physicsManager = new PhysicsManager();

  this->game = game;

  quit = false;
}

Engine::~Engine(void)
{
  delete window;
  delete glew_manager;
  delete gl_manager;
  delete m_physicsManager;
}

void Engine::start(void)
{
  game->setEngine(this);

  log_info("Initializing game");
  game->init(gl_manager);

  game->getRootScene()->registerWithEngineAll(this);

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
    Ray ray = Ray::getPickRay(window->getInput()->getMousePosition(), window->getViewport(), gl_manager->getViewMatrix(), gl_manager->getProjectionMatrix());

    Entity *pickedEntity = m_physicsManager->pick(&ray);

    if (pickedEntity != NULL)
      gl_manager->drawEntity(pickedEntity);

    gl_manager->drawLine(ray.getLine(100.0f));
  }

  window->swapBuffer();
}

Window *Engine::getWindow(void)
{
  return window;
}

GLManager *Engine::getGLManager(void)
{
  return gl_manager;
}

PhysicsManager *Engine::getPhysicsManager(void)
{
  return m_physicsManager;
}
