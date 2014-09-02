#include "EntityComponent.h"

void EntityComponent::setParent(Entity *parentEntity)
{
  this->parentEntity = parentEntity;
}

void EntityComponent::getTransform(void)
{
  return parentEntity->getTransform();
}
