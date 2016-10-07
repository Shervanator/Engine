#include "Octree.h"

Octree::Octree(const glm::vec3& min, const glm::vec3& max)
{
  a = min;
  b = max;
}

Octree::~Octree()
{}

void Octree::insert(Entity *entity)
{
  entity->getPosition();
}
