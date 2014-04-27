#ifndef GL_MANAGER_H
#define GL_MANAGER_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

class GLManager
{
public:
  GLManager(int width, int height);
  ~GLManager(void);

  void tick(int delta_time);

  void setViewProjection(const glm::mat4& viewProj);

private:
  void createShaders(void);

  Shader *active_shader;

  Shader *shader1;
  Shader *shader2;

  Mesh *model;
  Texture *texture;

  glm::mat4 viewProj;
};

#endif
