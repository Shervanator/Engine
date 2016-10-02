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

  m_properties["scale"] = (Property){FLOAT, &m_scale, 0, 200};
  m_properties["aspect"] = (Property){FLOAT, &m_aspect, 0, 10};
  m_properties["zNear"] = (Property){FLOAT, &m_zNear, 0, 1};
  m_properties["zFar"] = (Property){FLOAT, &m_zFar, 0, 1000};
}

glm::mat4 OrthoCamera::getProjectionMatrix(void) const
{
  return glm::ortho(-m_aspect * m_scale, m_aspect * m_scale, -1.0f * m_scale, 1.0f * m_scale, m_zNear, m_zFar);
}
