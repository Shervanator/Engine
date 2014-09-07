#include "Entity.h"

#include "EntityComponent.h"

Entity::Entity(void)
{
  parentEntity = NULL;
  transformedRotation = glm::quat();
}

Entity::~Entity(void)
{
  for (unsigned int i = 0; i < components.size(); i++)
  {
    delete components[i];
  }

  for (unsigned int i = 0; i < children.size(); i++)
  {
    delete children[i];
  }
}

void Entity::addChild(Entity* child)
{
  child->parentEntity = this;
  children.push_back(child);
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
    transformedRotation = transform.getRotation();
  } else {
    worldMatrix = parentEntity->worldMatrix * transform.getTransformMatrix();
    transformedRotation = parentEntity->transformedRotation * transform.getRotation();
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

glm::vec3 Entity::getPosition(void)
{
  if (parentEntity == NULL) {
    return transform.getPosition();
  } else {
    return glm::vec3(parentEntity->worldMatrix * glm::vec4(transform.getPosition(), 1));
  }
}

glm::quat Entity::getRotation(void)
{
  if (parentEntity == NULL) {
    return transform.getRotation();
  } else {
    // glm::mat4 temp = parentEntity->worldMatrix;
    // temp[0][0] = 1;
    // temp[1][1] = 1;
    // temp[2][2] = 1;
    // return glm::quat_cast(temp) * transform.getRotation(); // MIGHT BE ABLE TO GET THIS WORKING?

    // return glm::quat_cast(parentEntity->worldMatrix) * transform.getRotation(); // MIGHT BE ABLE TO GET THIS WORKING?

    return transformedRotation;

    // return parentEntity->getRotation() * transform.getRotation(); // WORKS
  }
}

glm::vec3 Entity::getDirection(void)
{
  if (parentEntity == NULL) {
    return transform.getDirection();
  } else {
    // return glm::vec3(parentEntity->worldMatrix * glm::vec4(transform.getDirection(), 1));
    // return parentEntity->getTransform().getDirection();
    // return transform.getDirection();
    return getRotation() * glm::vec3(0, 0, -1);
  }
}
