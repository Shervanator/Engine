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

  setProperty("scale", FLOAT, &m_scale, 0, 200);
  setProperty("aspect", FLOAT, &m_aspect, 0, 10);
  setProperty("zNear", FLOAT, &m_zNear, 0, 1);
  setProperty("zFar", FLOAT, &m_zFar, 0, 1000);
}

glm::mat4 OrthoCamera::getProjectionMatrix(void) const
{
  return glm::ortho(-m_aspect * m_scale, m_aspect * m_scale, -1.0f * m_scale, 1.0f * m_scale, m_zNear, m_zFar);
}
