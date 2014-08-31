#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

#include "Input.h"
#include "Shader.h"
#include "Entity.h"

class EntityComponent
{
public:
  virtual ~EntityComponent(void) {};

  virtual void updateInput(Input *input, int delta) {};
  virtual void update(int delta) {};
  virtual void render(Shader *shader) {};

  void setParent(Entity *parentEntity);

protected:
  Entity *parentEntity;
};

#endif
