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

  m_properties["fov"].type = ANGLE;
  m_properties["fov"].p = &m_fov;
  m_properties["fov"].min = 0;
  m_properties["fov"].max = 180;

  m_properties["aspect"].type = FLOAT;
  m_properties["aspect"].p = &m_aspect;
  m_properties["aspect"].min = 0;
  m_properties["aspect"].max = 10;

  m_properties["zNear"].type = FLOAT;
  m_properties["zNear"].p = &m_zNear;
  m_properties["zNear"].min = 0;
  m_properties["zNear"].max = 1;

  m_properties["zFar"].type = FLOAT;
  m_properties["zFar"].p = &m_zFar;
  m_properties["zFar"].min = 0;
  m_properties["zFar"].max = 1000;
}

glm::mat4 PerspectiveCamera::getProjectionMatrix(void) const
{
  return glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);
}
