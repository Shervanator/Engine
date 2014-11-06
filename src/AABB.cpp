#include "AABB.h"

AABB::AABB(float minX, float minY, float maxX, float maxY)
{
  m_minX = minX;
  m_minY = minY;
  m_maxX = maxX;
  m_maxY = maxY;
}

AABB::~AABB(void)
{
}

bool AABB::containsPoint(glm::vec4 point)
{
  return (point.x >= m_minX && point.x < m_maxX && point.y >= m_minY && point.y < m_maxY);
}

AABB *AABB::northWest(void)
{
  return new AABB(m_minX, m_maxY / 2.0f, m_maxX / 2.0f, m_maxY);
}

AABB *AABB::northEast(void)
{
  return new AABB(m_maxX / 2.0f, m_maxY / 2.0f, m_maxX, m_maxY);
}

AABB *AABB::southEast(void)
{
  return new AABB(m_maxX / 2.0f, m_minY, m_maxX, m_maxY / 2.0f);
}

AABB *AABB::southWest(void)
{
  return new AABB(m_minX, m_minY, m_maxX / 2.0f, m_maxY / 2.0f);
}

