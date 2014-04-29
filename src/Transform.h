#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
  Transform(const glm::vec3& position = glm::vec3(), const glm::quat& rotation = glm::quat(), const glm::vec3& scale = glm::vec3());
  ~Transform(void);

  glm::mat4 getTransform(void);

private:
  glm::vec3 position;
  glm::quat rotation;
  glm::vec3 scale;
};

#endif
