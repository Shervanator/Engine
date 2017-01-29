//
//  Author: Shervin Aflatooni
//

#include "Engine.h"
#include "Logger.h"
#include "Ray.h"
#include "GuiManager.h"

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
  gl_manager = new GLManager(window);

  log_info("Initializing Physics Manager");
  m_physicsManager = new PhysicsManager();

  this->game = game;

  quit = false;
}

Engine::~Engine(void)
{
  delete window;
  delete gl_manager;
  delete glew_manager;
  delete m_physicsManager;
}

void Engine::start(void)
{
  game->setEngine(this);

  game->getRootScene()->registerWithEngineAll(this);

  log_info("Initializing game");

  window->init();

  game->init(gl_manager);

  window->makeCurrentContext();

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

    if (pickedEntity != nullptr)
      gl_manager->drawEntity(pickedEntity);

    gl_manager->drawLine(ray.getLine(100.0f));
  }

  static bool f1Pressed = false;

  if (!f1Pressed && window->getInput()->isPressed(SDLK_F1)) {
    f1Pressed = true;
    window->getGuiManager()->togglePropertyEditor();
  } else if (f1Pressed && window->getInput()->isReleased(SDLK_F1)) {
    f1Pressed = false;
  }

  window->getGuiManager()->render(game->getRootScene().get());

  window->swapBuffer();
}

Window *Engine::getWindow(void) const
{
  return window;
}

GLManager *Engine::getGLManager(void) const
{
  return gl_manager;
}

PhysicsManager *Engine::getPhysicsManager(void) const
{
  return m_physicsManager;
}
