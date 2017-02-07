//
//  Author: Shervin Aflatooni
//

#include "Component.h"

void Component::setParent(Entity *parentEntity)
{
  m_parentEntity = parentEntity;
}

Entity *Component::getParent(void) const
{
  return m_parentEntity;
}

Transform& Component::getTransform(void) const
{
  return m_parentEntity->getTransform();
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
