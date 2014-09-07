#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include "Transform.h"
#include "Shader.h"
#include "Input.h"


class EntityComponent;

class Entity
{
public:
  Entity(void);
  ~Entity(void);

  void addChild(Entity* child);
  void addComponent(EntityComponent* component);

  void updateInputAll(Input *input, int delta);
  void updateAll(int delta);
  void renderAll(Shader *shader);

  Transform& getTransform(void);

  std::vector<Entity*> *getChildren(void);

  glm::mat4& getWorldMatrix(void);

  glm::vec3 getPosition(void);
  glm::quat getRotation(void);
  glm::vec3 getDirection(void);
private:
  Transform transform;

  Entity *parentEntity;

  std::vector<Entity*> children;
  std::vector<EntityComponent*> components;

  glm::mat4 worldMatrix;
  glm::quat transformedRotation;
};

#endif
