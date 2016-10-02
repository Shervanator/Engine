//
//  Author: Shervin Aflatooni
//

#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

#include "Input.h"
#include "Shader.h"
#include "Entity.h"
#include "Transform.h"

class Engine;

enum PropertyType {
  FLOAT,
  FLOAT3,
  BOOLEAN,
  ANGLE,
  COLOR
};

struct Property {
  PropertyType type;
  void *p;
  float min;
  float max;
};

class EntityComponent
{
public:
  virtual ~EntityComponent(void) {};

  virtual void updateInput(Input *input, int delta) {};
  virtual void update(int delta) {};
  virtual void render(Shader *shader) {};
  virtual void registerWithEngine(Engine *engine) {};
  virtual void deregisterFromEngine(Engine *engine) {};

  virtual const char *getType(void) = 0;

  void setProperty(const char *name, PropertyType type, void *p, float min, float max);
  void setProperty(const char *name, PropertyType type, void *p);

  void setParent(Entity *parentEntity);
  Entity *getParent(void) const;

  Transform& getTransform(void) const;

  std::map<const char *, Property> m_properties;

protected:
  Entity *parentEntity;
};

#endif
