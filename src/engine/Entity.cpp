//
//  Author: Shervin Aflatooni
//

#include "Entity.h"

#include "EntityComponent.h"

#include <algorithm>

std::map<std::string, std::vector<Entity*>> Entity::taggedEntities;

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

  for (unsigned int i = 0; i < components.size(); i++)
  {
    delete components[i];
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    delete children[i];
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

void Entity::addComponent(EntityComponent* component)
{
  component->setParent(this);
  components.push_back(component);
}

void Entity::updateInputAll(Input *input, int delta)
{
  if (parentEntity == NULL) {
    worldMatrix = transform.getTransformMatrix();
  } else {
    worldMatrix = parentEntity->worldMatrix * transform.getTransformMatrix();
  }

  for (unsigned int i = 0; i < components.size(); i++)
  {
    components[i]->updateInput(input, delta);
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    children[i]->updateInputAll(input, delta);
  }
}

void Entity::updateAll(int delta)
{
  for (unsigned int i = 0; i < components.size(); i++)
  {
    components[i]->update(delta);
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    children[i]->updateAll(delta);
  }
}

void Entity::renderAll(Shader *shader)
{
  for (unsigned int i = 0; i < components.size(); i++)
  {
    components[i]->render(shader);
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    children[i]->renderAll(shader);
  }
}

void Entity::registerWithEngineAll(Engine *engine)
{
  m_engine = engine;

  for (unsigned int i = 0; i < components.size(); i++)
  {
    components[i]->registerWithEngine(engine);
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    children[i]->registerWithEngineAll(engine);
  }
}

void Entity::deregisterFromEngineAll(void)
{
  for (unsigned int i = 0; i < components.size(); i++)
  {
    components[i]->deregisterFromEngine(m_engine);
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    children[i]->deregisterFromEngineAll();
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
