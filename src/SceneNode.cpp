#include "SceneNode.h"

SceneNode::SceneNode(void)
{
}

SceneNode::~SceneNode(void)
{
  for (unsigned int i = 0; i < gameObjects.size(); i++)
  {
    delete gameObjects[i];
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    delete children[i];
  }
}

void SceneNode::addChild(SceneNode* child)
{
  children.push_back(child);
}

void SceneNode::addObject(GameObject* object)
{
  gameObjects.push_back(object);
}

void SceneNode::update(int delta)
{
  for (unsigned int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->update(delta);
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    children[i]->update(delta);
  }
}

void SceneNode::render(void)
{
  for (unsigned int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->render();
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    children[i]->render();
  }
}
