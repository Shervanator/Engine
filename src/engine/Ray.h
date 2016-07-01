//
//  Author: Shervin Aflatooni
//

#ifndef RAY_H
#define RAY_H

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "components/Sphere.h"
#include "Line.h"

class Ray
{
public:
  Ray(glm::vec3 position, glm::vec3 direction);
  ~Ray(void);

  static Ray getPickRay(glm::vec2 mousePosition, const glm::vec4 &viewport, const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix);

  bool intersects(Sphere *sphere, glm::vec3 & intersectionPosition);

  glm::vec3 getPosition(void);
  glm::vec3 getDirection(void);

  Line getLine(float length);

private:
  glm::vec3 m_position;
  glm::vec3 m_direction;
};

#endif
