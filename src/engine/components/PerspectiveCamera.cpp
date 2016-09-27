//
//  Author: Shervin Aflatooni
//

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float zNear, float zFar)
{
  m_fov = fov;
  m_aspect = aspect;
  m_zNear = zNear;
  m_zFar = zFar;

  m_properties["fov"] = Property{ANGLE, &m_fov, 0, 180};
  m_properties["aspect"] = Property{FLOAT, &m_aspect, 0, 10};
  m_properties["zNear"] = Property{FLOAT, &m_zNear, 0, 1};
  m_properties["zFar"] = Property{FLOAT, &m_zFar, 0, 1000};
}

glm::mat4 PerspectiveCamera::getProjectionMatrix(void) const
{
  return glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);
}
