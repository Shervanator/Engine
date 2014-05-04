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

void Game::update(int delta, KeyboardHandler *keyboardHandler)
{
  rootScene.updateAll(delta);
}

void Game::render(GLManager *glManager)
{
  glManager->renderScene(&rootScene);
}
