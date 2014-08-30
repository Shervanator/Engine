#ifndef CAMERA_H
#define CAMERA_H

#include "EntityComponent.h"

#include <glm/glm.hpp>

class Camera : public EntityComponent
{
public:
  Camera(float fov, float aspect, float zNear, float zFar);
  ~Camera(void);

  void moveX(float x);
  void moveY(float y);
  void moveZ(float z);
  void update(int delta);

  void setAspect(float aspect);
  glm::mat4 getViewProjection(void);

private:
  glm::mat4 projection;

  glm::vec3 moveDirection;
  glm::vec3 velocity;
  glm::vec3 direction;

  float fov, zNear, zFar;
};

#endif
