#include "EntityComponent.h"

void EntityComponent::setParent(Entity *parentEntity)
{
  this->parentEntity = parentEntity;
}

Transform& EntityComponent::getTransform(void)
{
  return parentEntity->getTransform();
}
