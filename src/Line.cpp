#include "Line.h"

Line::Line(glm::vec3 v1, glm::vec3 v2)
{
  glm::vec3 vertices[] = { v1, v2 };

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec3), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

  glBindVertexArray(0);
}

Line::~Line(void)
{
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}

void Line::render(Shader *shader)
{
  glBindVertexArray(vao);
  glDrawArrays(GL_LINES, 0, 2);
  glBindVertexArray(0);
}
