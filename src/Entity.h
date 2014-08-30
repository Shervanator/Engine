#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include "Shader.h"

#include "Transform.h"

class EntityComponent;

class Entity
{
public:
  Entity(void);
  ~Entity(void);

  void addChild(Entity* child);
  void addComponent(EntityComponent* component);

  void updateAll(int delta);
  void renderAll(Shader *shader);

  Transform& getTransform(void);

  std::vector<Entity*> *getChildren(void);

  glm::mat4& getWorldMatrix(void);
private:
  Transform transform;

  Entity *parentEntity;

  std::vector<Entity*> children;
  std::vector<EntityComponent*> components;

  glm::mat4 worldMatrix;
};

#endif
