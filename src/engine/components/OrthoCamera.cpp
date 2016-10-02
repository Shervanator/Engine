//
//  Author: Shervin Aflatooni
//

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "OrthoCamera.h"

OrthoCamera::OrthoCamera(float aspect, float scale, float zNear, float zFar)
{
  m_scale = scale;
  m_aspect = aspect;
  m_zNear = zNear;
  m_zFar = zFar;

  m_properties["scale"].type = FLOAT;
  m_properties["scale"].p = &m_scale;
  m_properties["scale"].min = 0;
  m_properties["scale"].max = 200;

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

glm::mat4 OrthoCamera::getProjectionMatrix(void) const
{
  return glm::ortho(-m_aspect * m_scale, m_aspect * m_scale, -1.0f * m_scale, 1.0f * m_scale, m_zNear, m_zFar);
}
