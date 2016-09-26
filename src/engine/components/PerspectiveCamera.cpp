//
//  Author: Shervin Aflatooni
//

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float zNear, float zFar)
{
  this->projection = glm::perspective(fov, aspect, zNear, zFar);
}
