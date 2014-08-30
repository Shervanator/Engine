#include "Entity.h"

#include "EntityComponent.h"

Entity::Entity(void)
{
  parentEntity = NULL;
}

Entity::~Entity(void)
{
  for (unsigned int i = 0; i < components.size(); i++)
  {
    delete components[i];
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    delete children[i];
  }
}

void Entity::addChild(Entity* child)
{
  child->parentEntity = this;
  children.push_back(child);
}

void Entity::addComponent(EntityComponent* component)
{
  component->setParent(this);
  components.push_back(component);
}

void Entity::updateInputAll(Input *input, int delta)
{
  if (parentEntity == NULL) {
    worldMatrix = transform.getTransformMatrix();
  } else {
    worldMatrix = parentEntity->worldMatrix * transform.getTransformMatrix();
  }

  for (unsigned int i = 0; i < components.size(); i++)
  {
    components[i]->updateInput(input, delta);
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    children[i]->updateInputAll(input, delta);
  }
}

void Entity::updateAll(int delta)
{
  for (unsigned int i = 0; i < components.size(); i++)
  {
    components[i]->update(delta);
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    children[i]->updateAll(delta);
  }
}

void Entity::renderAll(Shader *shader)
{
  for (unsigned int i = 0; i < components.size(); i++)
  {
    components[i]->render(shader);
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    children[i]->renderAll(shader);
  }
}

Transform& Entity::getTransform(void)
{
  return transform;
}

std::vector<Entity*> *Entity::getChildren(void)
{
  return &children;
}

glm::mat4& Entity::getWorldMatrix(void)
{
  return worldMatrix;
}
