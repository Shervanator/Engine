//
//  Author: Shervin Aflatooni
//

#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "BaseLight.h"

class PointLight : public BaseLight
{
public:
  PointLight(glm::vec3 color, float intensity, Attenuation *attenuation);
  virtual ~PointLight(void);
  virtual void registerWithEngine(Engine *engine);

  virtual void updateShader(Shader *shader);

  Attenuation *getAttenuation(void);
  float getRange(void);

private:
  Attenuation *m_attenuation;

  float m_range;
};

#endif
