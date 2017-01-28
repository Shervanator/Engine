//
//  Author: Shervin Aflatooni
//

#include "Component.h"

void Component::setParent(Entity *parentEntity)
{
  this->parentEntity = parentEntity;
}

Entity *Component::getParent(void) const
{
  return parentEntity;
}

Transform& Component::getTransform(void) const
{
  return parentEntity->getTransform();
}

void Component::setProperty(const char *name, PropertyType type, void *p, float min, float max)
{
  Property prop;

  prop.type = type;
  prop.p = p;
  prop.min = min;
  prop.max = max;

  m_properties[name] = prop;
}

void Component::setProperty(const char *name, PropertyType type, void *p)
{
  Property prop;

  prop.type = type;
  prop.p = p;

  m_properties[name] = prop;
}
