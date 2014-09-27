#ifndef MESH_H
#define MESH_H

#if defined(GLES2)
  #include <GLES2/gl2.h>
#elif defined(GLES3)
  #include <GLES3/gl3.h>
#else
  #include <GL/glew.h>
#endif

#include "Vertex.h"

class Mesh
{
public:
  Mesh(Vertex vertices[], int vertSize, unsigned int indices[], int indexSize);
  virtual ~Mesh(void);

  void createMesh(Vertex vertices[], int vertSize, unsigned int indices[], int indexSize);
  void render(void);

private:
#if !defined(GLES2)
  GLuint vao;
#endif
  GLuint vbo;
  GLuint ibo;

  int indexSize, vertSize;
};

#endif
