#include "SceneNode.h"

#include "GameObject.h"

SceneNode::SceneNode(void)
{
  parentNode = NULL;
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
  child->parentNode = this;
  children.push_back(child);
}

void SceneNode::addObject(GameObject* object)
{
  object->setParent(this);
  gameObjects.push_back(object);
}

void SceneNode::updateAll(int delta)
{
  if (parentNode == NULL) {
    worldMatrix = transform.getTransformMatrix();
  } else {
    worldMatrix = parentNode->worldMatrix * transform.getTransformMatrix();
  }

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

Transform& SceneNode::getTransform(void)
{
  return transform;
}

std::vector<SceneNode*> *SceneNode::getChildren(void)
{
  return &children;
}

glm::mat4& SceneNode::getWorldMatrix(void)
{
  return worldMatrix;
}
