//
//  Author: Shervin Aflatooni
//

#include "EntityComponent.h"

void EntityComponent::setParent(Entity *parentEntity)
{
  this->parentEntity = parentEntity;
}

Entity *EntityComponent::getParent(void) const
{
  return parentEntity;
}

Transform& EntityComponent::getTransform(void) const
{
  return parentEntity->getTransform();
}
