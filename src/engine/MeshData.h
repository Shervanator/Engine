//
//  Author: Shervin Aflatooni
//

#pragma once

#if defined(GLES2)
  #include <GLES2/gl2.h>
#elif defined(GLES3)
  #include <GLES3/gl3.h>
#else
  #include <GL/glew.h>
#endif

#include "Vertex.h"

class MeshData
{
public:
  MeshData(Vertex vertices[], int vertSize, unsigned int indices[], int indexSize);
  virtual ~MeshData(void);
  void render(void) const;

private:
  void createMesh(Vertex vertices[], int vertSize, unsigned int indices[], int indexSize);

#if !defined(GLES2)
  GLuint m_vao;
#endif
  GLuint m_vbo;
  GLuint m_ibo;

  int m_indexSize, m_vertSize;
};
