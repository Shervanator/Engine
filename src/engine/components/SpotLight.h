//
//  Author: Shervin Aflatooni
//

#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "PointLight.h"

class SpotLight : public PointLight
{
public:
  SpotLight(glm::vec3 color, float intensity, float cutoff, Attenuation *attenuation);
  virtual void registerWithEngine(Engine *engine);
  virtual void deregisterFromEngine(Engine *engine);

  virtual void updateShader(Shader *shader);

  float getCutoff(void) const;

private:
  float m_cutoff;
};

#endif
