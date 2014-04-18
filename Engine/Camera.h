#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
  Camera(const glm::vec3& position, float fov, float aspect, float zNear, float zFar);
  ~Camera(void);

  void setMousePosition(int xDelta, int yDelta);
  void moveX(float x);
  void moveY(float y);
  void moveZ(float z);
  void tick(int delta_time);

  glm::vec3 getPosition(void);
  glm::vec3 getDirection(void);
  glm::vec3 getUp(void);

  glm::mat4 getViewProjection(void);

private:
  glm::vec3 position;

  glm::mat4 projection;
  glm::vec3 up;

  glm::vec3 moveDirection;
  glm::vec3 velocity;
  glm::vec3 direction;

  float horizontalAngle;
  float verticalAngle;
  int xDelta, yDelta;
};

#endif
