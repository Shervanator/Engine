#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class Model
{
public:
  Model(void);
  ~Model(void);

  void render(void);

private:
  GLuint  g_vao;
  GLuint  g_vbo;

  glm::vec3 position;
};

#endif
