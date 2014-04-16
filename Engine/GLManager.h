#ifndef GL_MANAGER_H
#define GL_MANAGER_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Shader.h"
#include "Model.h"

class GLManager
{
public:
  GLManager(void);
  ~GLManager(void);

  void clean(void);

  int init(const int width, const int height);

  void tick(int delta_time);

  void setLookAt(glm::vec3 position, glm::vec3 direction, glm::vec3 up);

private:
  void createShaders(void);

  Shader *active_shader;

  Shader *shader1;
  Shader *shader2;

  Model *model;

  glm::mat4 view;
  glm::mat4 projection;
};

#endif
