//
//  Author: Shervin Aflatooni
//

#ifndef LINE_H
#define LINE_H

#include "Shader.h"

#include <glm/glm.hpp>

class Line
{
public:
  Line(glm::vec3 v1, glm::vec3 v2);
  ~Line(void);

  void render(Shader *shader) const;

private:
#if !defined(GLES2)
  GLuint vao;
#endif
  GLuint vbo;
};

#endif
