#include "Mesh.h"

#include <iostream>

Mesh::Mesh(Vertex vertices[], int vertSize, unsigned int indices[], int indexSize)
{
  createMesh(vertices, vertSize, indices, indexSize);
}

Mesh::~Mesh(void)
{
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}

void Mesh::createMesh(Vertex vertices[], int vertSize, unsigned int indices[], int indexSize)
{
  this->vertSize  = vertSize;
  this->indexSize = indexSize;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertSize, indices, GL_STATIC_DRAW);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(glm::vec3));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2) + sizeof(glm::vec3)));

  glBindVertexArray(0);
}

void Mesh::render(void)
{
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, (void*)0);
  glBindVertexArray(0);
}