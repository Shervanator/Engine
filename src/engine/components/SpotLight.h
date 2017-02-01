//
//  Author: Shervin Aflatooni
//

#pragma once

#include "PointLight.h"

class SpotLight : public PointLight
{
public:
  SpotLight(glm::vec3 color, float intensity, float cutoff, std::shared_ptr<Attenuation> attenuation);
  virtual void registerWithEngine(Engine *engine);
  virtual void deregisterFromEngine(Engine *engine);

  inline virtual const char *getType(void) { return "SPOT_LIGHT"; }

  virtual void updateShader(Shader *shader);

  float getCutoff(void) const;

private:
  float m_cutoff;
};
