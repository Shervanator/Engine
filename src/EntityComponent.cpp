#include "EntityComponent.h"

void EntityComponent::setParent(Entity *parentEntity)
{
  this->parentEntity = parentEntity;
}
