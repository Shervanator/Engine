#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "Entity.h"
#include "AABB.h"

class QuadTree
{
public:
  QuadTree(AABB *aabb);
  ~QuadTree(void);

  bool insert(Entity *entity);

private:
  QuadTree* northWest;
  QuadTree* northEast;
  QuadTree* southEast;
  QuadTree* southWest;

  Entity *m_entity;

  AABB *m_aabb;
};

#endif
