//
//  Author: Shervin Aflatooni
//

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

void Entity::calculateWorldMatrix(void)
{
  if (parentEntity == NULL) {
    worldMatrix = transform.getTransformMatrix();
  } else {
    worldMatrix = parentEntity->worldMatrix * transform.getTransformMatrix();
  }
}

void Entity::updateInputAll(Input *input, int delta)
{
  calculateWorldMatrix();

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

void Entity::registerWithEngineAll(Engine *engine)
{
  for (unsigned int i = 0; i < components.size(); i++)
  {
    components[i]->registerWithEngine(engine);
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    children[i]->registerWithEngineAll(engine);
  }
}


Transform& Entity::getTransform(void)
{
  return transform;
}

Entity* Entity::getParent(void)
{
  return parentEntity;
}

std::vector<Entity*> *Entity::getChildren(void)
{
  return &children;
}

glm::mat4& Entity::getWorldMatrix(void)
{
  return worldMatrix;
}

glm::vec4 Entity::getPosition(void)
{
  if (parentEntity == NULL) {
    return transform.getPosition();
  } else {
    return parentEntity->worldMatrix * transform.getPosition();
  }
}

glm::vec4 Entity::getDirection(void)
{
  if (parentEntity == NULL) {
    return transform.getDirection();
  } else {
    return glm::normalize(parentEntity->worldMatrix * transform.getDirection());
  }
}
