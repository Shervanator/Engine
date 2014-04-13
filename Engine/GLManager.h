#ifndef GL_MANAGER_H
#define GL_MANAGER_H

#include <glm/glm.hpp>

#include "Shader.h"

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
  void createVAO(void);
  void createShaders(void);

  GLuint  g_vao;
  GLuint  g_vbo;

  Shader *shader1;
  Shader *shader2;

  glm::mat4 view;
};

#endif
