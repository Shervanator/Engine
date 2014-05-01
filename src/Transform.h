#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
  Transform(const glm::vec3& position = glm::vec3(), const glm::quat& rotation = glm::quat(), const glm::vec3& scale = glm::vec3(1.0f));
  ~Transform(void);

  void setPosition(const glm::vec3& position);

  void setScale(const glm::vec3& scale);

  void setRotation(const glm::quat& rotation);
  void setRotation(const glm::vec3& axis, float w);

  glm::vec3 getPosition(void);
  glm::vec3 getScale(void);
  glm::quat getRotation(void);

  glm::mat4 getTransformMatrix(void);

private:
  glm::vec3 position;
  glm::quat rotation;
  glm::vec3 scale;
};

#endif
