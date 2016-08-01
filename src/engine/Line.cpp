//
//  Author: Shervin Aflatooni
//

#include "Line.h"

Line::Line(glm::vec3 v1, glm::vec3 v2)
{
  glm::vec3 vertices[] = { v1, v2 };

#if !defined(GLES2)
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
#endif

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec3), vertices, GL_STATIC_DRAW);

#if !defined(GLES2)
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

  glBindVertexArray(0);
#endif
}

Line::~Line(void)
{
  glDeleteBuffers(1, &vbo);
#if !defined(GLES2)
  glDeleteVertexArrays(1, &vao);
#endif
}

void Line::render(Shader *shader) const
{
#if defined(GLES2)
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

  glDrawArrays(GL_LINES, 0, 2);

  glDisableVertexAttribArray(0);
#else
  glBindVertexArray(vao);
  glDrawArrays(GL_LINES, 0, 2);
  glBindVertexArray(0);
#endif
}
