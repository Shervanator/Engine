//
//  Author: Shervin Aflatooni
//

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "OrthoCamera.h"

OrthoCamera::OrthoCamera(float aspect, float scale, float zNear, float zFar)
{
  this->projection = glm::ortho(-aspect * scale, aspect * scale, -1.0f * scale, 1.0f * scale, zNear, zFar);
}
