//
//  Author: Shervin Aflatooni
//

#pragma once

#include <memory>

#include "BaseLight.h"

class PointLight : public BaseLight
{
public:
  PointLight(glm::vec3 color, float intensity, std::shared_ptr<Attenuation> attenuation);
  virtual ~PointLight(void);
  virtual void registerWithEngine(Engine *engine);
  virtual void deregisterFromEngine(Engine *engine);

  virtual void updateShader(Shader *shader);

  inline virtual const char *getType(void) { return "POINT_LIGHT"; }

  std::shared_ptr<Attenuation> getAttenuation(void) const;
  float getRange(void);

private:
  std::shared_ptr<Attenuation> m_attenuation;

  float m_range;
};
