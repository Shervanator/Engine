//
//  Author: Shervin Aflatooni
//

#ifndef CAMERA_H
#define CAMERA_H

#include "../EntityComponent.h"

#include <glm/glm.hpp>

class Camera : public EntityComponent
{
public:
  virtual ~Camera(void) {}

  glm::mat4 getViewMatrix(void) const;
  virtual glm::mat4 getProjectionMatrix(void) const = 0;

  inline virtual const char *getType(void) { return "CAMERA"; }
};

#endif
