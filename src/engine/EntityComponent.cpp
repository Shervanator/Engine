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

void EntityComponent::setProperty(const char *name, PropertyType type, void *p, float min, float max)
{
  Property prop;

  prop.type = type;
  prop.p = p;
  prop.min = min;
  prop.max = max;

  m_properties[name] = prop;
}

void EntityComponent::setProperty(const char *name, PropertyType type, void *p)
{
  Property prop;

  prop.type = type;
  prop.p = p;

  m_properties[name] = prop;
}
