//
//  Author: Shervin Aflatooni
//

#include "EntityComponent.h"

void EntityComponent::setParent(Entity *parentEntity)
{
  this->parentEntity = parentEntity;
}

Entity *EntityComponent::getParent(void)
{
  return parentEntity;
}

Transform& EntityComponent::getTransform(void)
{
  return parentEntity->getTransform();
}
