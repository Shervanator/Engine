//
//  Author: Shervin Aflatooni
//

#ifndef BASE_LIGHT_H
#define BASE_LIGHT_H

#include <glm/glm.hpp>

#include "../Component.h"
#include "../Shader.h"

class BaseLight : public Component
{
public:
  BaseLight(glm::vec3 color, float intensity);
  virtual ~BaseLight(void);

  virtual void registerWithEngine(Engine *engine) {};

  glm::vec3 getColor(void) const;
  float getIntensity(void) const;

  virtual void updateShader(Shader *shader) = 0;

protected:
  glm::vec3 m_color;
  float m_intensity;
};

#endif
