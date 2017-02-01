//
//  Author: Shervin Aflatooni
//

#pragma once

#include "Camera.h"

#include <glm/glm.hpp>

class OrthoCamera : public Camera
{
public:
  OrthoCamera(float aspect, float scale, float zNear, float zFar);

  virtual glm::mat4 getProjectionMatrix(void) const;

  inline virtual const char *getType(void) { return "ORTHO_CAMERA"; }

private:
  float m_scale, m_aspect, m_zNear, m_zFar;
};
