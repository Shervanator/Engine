//
//  Author: Shervin Aflatooni
//

#include "Entity.h"

#include "EntityComponent.h"

#include <algorithm>

std::map<std::string, std::vector<Entity*> > Entity::taggedEntities;

Entity::Entity(const std::string& tag)
{
  Entity::setTag(this, tag);

  m_tag = tag;
  parentEntity = NULL;
}

Entity::Entity(void)
{
  parentEntity = NULL;
}

Entity::~Entity(void)
{
  if (!m_tag.empty()) {
    auto taggedEntitiesVec = &Entity::taggedEntities[m_tag];
    taggedEntitiesVec->erase(std::remove(taggedEntitiesVec->begin(), taggedEntitiesVec->end(), this), taggedEntitiesVec->end());
  }

  for (auto component : components)
  {
    delete component;
  }

  for (auto child : children)
  {
    delete child;
  }
}

void Entity::setTag(Entity *entity, const std::string& tag)
{
  Entity::taggedEntities[tag].push_back(entity);
}

std::vector<Entity*> Entity::findByTag(const std::string& tag)
{
  return Entity::taggedEntities[tag];
}

void Entity::addChild(Entity* child)
{
  child->parentEntity = this;
  children.push_back(child);

  // FIXME: IF MOVING ENTITY TO ANOTHER ENTITY THIS WILL BE AN ISSUE AS WE WILL REREGISTER
  if (m_engine) {
    child->registerWithEngineAll(m_engine);
  }
}

void Entity::updateInputAll(Input *input, int delta)
{
  if (parentEntity == NULL) {
    worldMatrix = transform.getTransformMatrix();
  } else {
    worldMatrix = parentEntity->worldMatrix * transform.getTransformMatrix();
  }

  for (auto component : components)
  {
    component->updateInput(input, delta);
  }

  for (auto child : children)
  {
    child->updateInputAll(input, delta);
  }
}

void Entity::updateAll(int delta)
{
  for (auto component : components) {
    component->update(delta);
  }

  for (auto child : children)
  {
    child->updateAll(delta);
  }
}

void Entity::renderAll(Shader *shader)
{
  for (auto component : components)
  {
    component->render(shader);
  }

  for (auto child : children)
  {
    child->renderAll(shader);
  }
}

void Entity::registerWithEngineAll(Engine *engine)
{
  m_engine = engine;

  for (auto component : components)
  {
    component->registerWithEngine(engine);
  }

  for (auto child : children)
  {
    child->registerWithEngineAll(engine);
  }
}

void Entity::deregisterFromEngineAll(void)
{
  for (auto component : components)
  {
    component->deregisterFromEngine(m_engine);
  }

  for (auto child : children)
  {
    child->deregisterFromEngineAll();
  }

  m_engine = nullptr;
}

Transform& Entity::getTransform(void)
{
  return transform;
}

std::vector<Entity*> *Entity::getChildren(void)
{
  return &children;
}

std::vector<EntityComponent*> *Entity::getComponents(void)
{
  return &components;
}

glm::mat4& Entity::getWorldMatrix(void)
{
  return worldMatrix;
}

glm::vec4 Entity::getPosition(void)
{
  if (parentEntity == NULL) {
    return transform.getPosition();
  } else {
    return parentEntity->worldMatrix * transform.getPosition();
  }
}

glm::vec4 Entity::getDirection(void)
{
  if (parentEntity == NULL) {
    return transform.getDirection();
  } else {
    return glm::normalize(parentEntity->worldMatrix * transform.getDirection());
  }
}
