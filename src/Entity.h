//
//  Author: Shervin Aflatooni
//

#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>

#include "Transform.h"
#include "Shader.h"
#include "Input.h"

class Engine;

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
  void registerWithEngineAll(Engine *engine);

  Entity* getParent(void);

  Transform& getTransform(void);

  std::vector<Entity*> *getChildren(void);

  glm::mat4& getWorldMatrix(void);

  glm::vec4 getPosition(void);
  glm::vec4 getDirection(void);

  void calculateWorldMatrix(void);

  std::string name;
private:
  Transform transform;

  Entity *parentEntity;

  std::vector<Entity*> children;
  std::vector<EntityComponent*> components;

  glm::mat4 worldMatrix;
};

#endif
