#ifndef MESH_H
#define MESH_H

#ifndef EMSCRIPTEN
  #include <GL/glew.h>
#else
  #include <GLES2/gl2.h>
  #include <GLES2/gl2ext.h>
#endif
#include <glm/glm.hpp>

#include "Vertex.h"

class Mesh
{
public:
  Mesh(const char* file);
  Mesh(Vertex vertices[], int vertSize, unsigned int indices[], int indexSize);
  ~Mesh(void);

  void createMesh(Vertex vertices[], int vertSize, unsigned int indices[], int indexSize);
  void render(void);

private:
#ifndef EMSCRIPTEN
  GLuint vao;
#endif
  GLuint vbo;
  GLuint ibo;

  glm::vec3 position;

  int indexSize, vertSize;
};

#endif
