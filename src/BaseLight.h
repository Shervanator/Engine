#ifndef BASE_LIGHT_H
#define BASE_LIGHT_H

#include <glm/glm.hpp>

#include "EntityComponent.h"
#include "Shader.h"

class BaseLight : public EntityComponent
{
public:
  BaseLight(glm::vec3 color, float intensity);
  virtual ~BaseLight(void);

  glm::vec3 getColor(void);
  float getIntensity(void);

  virtual void updateShader(Shader *shader) = 0;

private:
  glm::vec3 m_color;
  float m_intensity;
};

#endif
