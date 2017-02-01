//
//  Author: Shervin Aflatooni
//

#pragma once

#define GLM_SWIZZLE
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
  Transform(const glm::vec3& position = glm::vec3(), const glm::quat& rotation = glm::quat(), const glm::vec3& scale = glm::vec3(1.0f));
  ~Transform(void);

  void rotate(const glm::vec3& axis, float angle);
  void scale(float scale);
  void scale(const glm::vec3& scale);
  void translate(const glm::vec3& position);

  void setPosition(const glm::vec3& position);

  void setScale(const glm::vec3& scale);

  void setRotation(const glm::quat& rotation);
  void setRotation(const glm::vec3& axis, float w);

  glm::vec4 getPosition(void) const;
  glm::vec3 getScale(void) const;
  glm::quat getRotation(void) const;

  glm::mat4 getTransformMatrix(void) const;

  glm::vec4 getDirection(void) const;

// private:
  glm::vec4 m_position;
  glm::quat m_rotation;
  glm::vec3 m_scale;
};
