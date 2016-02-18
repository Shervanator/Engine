//
//  Author: Shervin Aflatooni
//

#include "Game.h"

Game::Game(void)
{
  scenes.push_back(new Entity());
}

Game::~Game(void)
{
}

void Game::setEngine(Engine *engine)
{
  this->engine = engine;
}

Engine *Game::getEngine(void)
{
  return engine;
}

void Game::init(GLManager *glManager)
{
}

void Game::addToScene(Entity *entity, int sceneIndex)
{
  if (scenes.size() < sceneIndex + 1) {
    scenes.push_back(new Entity());
  }

  scenes[sceneIndex]->addChild(entity);
}

void Game::updateInput(Input *input, int delta)
{
  for (auto scene : scenes) {
    scene->updateInputAll(input, delta);
  }
}

void Game::update(int delta)
{
  for (auto scene : scenes) {
    scene->updateAll(delta);
  }
}

void Game::render(GLManager *glManager)
{
  glManager->renderScenes(scenes);
}
