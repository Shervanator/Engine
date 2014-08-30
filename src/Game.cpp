#include "Game.h"

Game::Game(void)
{
}

Game::~Game(void)
{
}

void Game::init(void)
{
}

void Game::addToScene(Entity *entity)
{
  rootScene.addChild(entity);
}

void Game::updateInput(Input *input, int delta)
{
  rootScene.updateInputAll(input, delta);
}

void Game::update(int delta)
{
  rootScene.updateAll(delta);
}

void Game::render(GLManager *glManager)
{
  glManager->renderScene(&rootScene);
}
