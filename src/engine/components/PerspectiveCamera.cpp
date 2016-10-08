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

  setProperty("fov", ANGLE, &m_fov, 0, 180);
  setProperty("aspect", FLOAT, &m_aspect, 0, 10);
  setProperty("zNear", FLOAT, &m_zNear, 0, 1);
  setProperty("zFar", FLOAT, &m_zFar, 0, 1000);
}

glm::mat4 PerspectiveCamera::getProjectionMatrix(void) const
{
  return glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);
}

void PerspectiveCamera::setFov(float fov)
{
  m_fov = fov;
}

float PerspectiveCamera::getFov(void)
{
  return m_fov;
}
