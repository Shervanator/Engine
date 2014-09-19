#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>

class Sphere
{
public:
  Sphere(glm::vec3 position, float radius);
  ~Sphere(void);

  glm::vec3 getPosition(void);
  float getRadius(void);

private:
  glm::vec3 m_position;
  float m_radius;
};

#endif
