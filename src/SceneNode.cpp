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

void SceneNode::updateAll(int delta)
{
  for (unsigned int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->update(delta);
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    children[i]->updateAll(delta);
  }
}

void SceneNode::renderAll(Shader *shader)
{
  for (unsigned int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->render(shader);
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    children[i]->renderAll(shader);
  }
}
