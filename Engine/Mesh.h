#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
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
  GLuint vao;
  GLuint vbo;
  GLuint ibo;

  glm::vec3 position;

  int indexSize, vertSize;
};

#endif
