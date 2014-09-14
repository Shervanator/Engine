#include "Plane.h"

Plane::Plane(void)
{
  Vertex vertices[] = {
    Vertex(glm::vec3(-0.5, 0, 0.5),  glm::vec2(0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
    Vertex(glm::vec3(0.5, 0, 0.5),   glm::vec2(1, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
    Vertex(glm::vec3(0.5, 0, -0.5),  glm::vec2(1, 1), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
    Vertex(glm::vec3(-0.5, 0, -0.5), glm::vec2(0, 1), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0))
  };

  unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3
  };

  mesh = new Mesh(vertices, 4, indices, 6);
}

Plane::~Plane(void)
{
  delete mesh;
}

Mesh *Plane::getMesh(void)
{
  return mesh;
}
