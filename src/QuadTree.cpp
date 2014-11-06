#include "QuadTree.h"

QuadTree::QuadTree(AABB *aabb)
{
  northWest = nullptr;
  northEast = nullptr;
  southEast = nullptr;
  southWest = nullptr;
  m_entity  = nullptr;

  m_aabb = aabb;
}

QuadTree::~QuadTree(void)
{
  delete m_aabb;

  if (northWest != nullptr) {
    delete northWest;
    delete northEast;
    delete southEast;
    delete southWest;
  }
}

bool QuadTree::insert(Entity *entity)
{
  if (!m_aabb->containsPoint(entity->getPosition()))
    return false;

  if (m_entity == nullptr) {
    m_entity = entity;
    return true;
  }

  northWest = new QuadTree(m_aabb->northWest());
  northEast = new QuadTree(m_aabb->northEast());
  southEast = new QuadTree(m_aabb->southEast());
  southWest = new QuadTree(m_aabb->southWest());

  return (northWest->insert(entity) || northEast->insert(entity) || southWest->insert(entity) || southEast->insert(entity));
}
