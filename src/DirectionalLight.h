#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "BaseLight.h"

class DirectionalLight : public BaseLight
{
  DirectionalLight(glm::vec3 color, float intensity) : BaseLight(color, intensity);
};

#endif
