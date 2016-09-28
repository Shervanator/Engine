//
//  Author: Shervin Aflatooni
//

#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "BaseLight.h"

class DirectionalLight : public BaseLight
{
public:
  DirectionalLight(glm::vec3 color, float intensity);
  virtual void registerWithEngine(Engine *engine);
  virtual void deregisterFromEngine(Engine *engine);

  virtual void updateShader(Shader *shader);

  inline virtual const char *getType(void) { return "DIRECTIONAL_LIGHT"; }
};

#endif
