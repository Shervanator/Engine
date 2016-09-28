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

  inline virtual const char *getType(void) { return "PERSPECTIVE_CAMERA"; }
};

#endif
