#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera : public GameObject
{
public:
  Camera(float fov, float aspect, float zNear, float zFar);
  ~Camera(void);

  void moveX(float x);
  void moveY(float y);
  void moveZ(float z);
  void update(int delta);

  glm::mat4 getViewProjection(void);

private:
  glm::mat4 projection;

  glm::vec3 moveDirection;
  glm::vec3 velocity;
  glm::vec3 direction;
};

#endif
