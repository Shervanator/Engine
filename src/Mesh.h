#ifndef MESH_H
#define MESH_H

#include "Vertex.h"
#include "MeshData.h"

#include <string>

class Mesh
{
public:
  Mesh(std::string identifier, Vertex vertices[], int vertSize, unsigned int indices[], int indexSize);
  ~Mesh(void);

  void render(void);

private:
  MeshData *m_meshData;
};

#endif
