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

void Game::addToScene(SceneNode *node)
{
  rootScene.addChild(node);
}

void Game::update(int delta)
{
  rootScene.update(delta);
}

void Game::render(void)
{
  rootScene.render();
}
