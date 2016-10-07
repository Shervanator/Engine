#ifndef OCTREE_H
#define OCTREE_H

#include <glm/glm.hpp>

#include "Entity.h"

class Octree {
public:
  Octree(const glm::vec3& min, const glm::vec3& max);
  ~Octree();

  void insert(Entity *entity);

private:
  Octree *children[8];

  glm::vec3 a;
  glm::vec3 b;
};

#endif
