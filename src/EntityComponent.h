#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

#include "Shader.h"
#include "Entity.h"

class EntityComponent
{
public:
  virtual ~EntityComponent(void) {};

  virtual void update(int delta) = 0;
  virtual void render(Shader *shader) {};

  void setParent(Entity *parentEntity);

protected:
  Entity *parentEntity;
};

#endif
