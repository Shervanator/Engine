//
//  Author: Shervin Aflatooni
//

#ifndef ORTHO_CAMERA_H
#define ORTHO_CAMERA_H

#include "Camera.h"

#include <glm/glm.hpp>

class OrthoCamera : public Camera
{
public:
  OrthoCamera(float aspect, float scale, float zNear, float zFar);
};

#endif
