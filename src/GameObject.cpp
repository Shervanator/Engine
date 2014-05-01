#include "GameObject.h"

#include "SceneNode.h"

glm::mat4 GameObject::getTransformMatrix(void)
{
  return parentNode->getTransformMatrix() * transform.getTransformMatrix();
}

Transform& GameObject::getTransform(void)
{
  return transform;
}
