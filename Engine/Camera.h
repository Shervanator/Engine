#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:
  Camera(void);
  ~Camera(void);

  void setMousePosition(int xDelta, int yDelta);
  void tick(int delta_time, int x = 0, int y = 0);

  glm::vec3 getPosition(void);
  glm::vec3 getDirection(void);
  glm::vec3 getUp(void);

private:
  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 up;

  float horizontalAngle;
  float verticalAngle;
  int xDelta, yDelta;
};

#endif
