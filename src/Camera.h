#ifndef CAMERA_H
#define CAMERA_H

#include "EntityComponent.h"

#include <glm/glm.hpp>

class Camera : public EntityComponent
{
public:
  Camera(float fov, float aspect, float zNear, float zFar);
  ~Camera(void);

  glm::mat4 getViewMatrix(void);
  glm::mat4 getProjectionMatrix(void);

private:
  glm::mat4 projection;
};

#endif
