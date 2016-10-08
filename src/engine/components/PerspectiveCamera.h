//
//  Author: Shervin Aflatooni
//

#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "Camera.h"

#include <glm/glm.hpp>

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera(float fov, float aspect, float zNear, float zFar);

  virtual glm::mat4 getProjectionMatrix(void) const;

  inline virtual const char *getType(void) { return "PERSPECTIVE_CAMERA"; }

  void setFov(float fov);
  float getFov(void);

private:
  float m_fov, m_aspect, m_zNear, m_zFar;
};

#endif
