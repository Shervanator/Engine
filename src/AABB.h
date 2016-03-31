#ifndef AABB_H
#define AABB_H

#define GLM_SWIZZLE
#include <glm/glm.hpp>

class AABB
{
public:
  AABB(float minX, float minY, float maxX, float maxY);
  ~AABB(void);

  bool containsPoint(glm::vec4 point);

  AABB *northWest(void);
  AABB *northEast(void);
  AABB *southEast(void);
  AABB *southWest(void);

private:
  float m_minX;
  float m_minY;
  float m_maxX;
  float m_maxY;
};

#endif
