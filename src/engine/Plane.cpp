//
//  Author: Shervin Aflatooni
//

#include "Plane.h"

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

Plane::Plane(void)
{
}

std::shared_ptr<Mesh> Plane::getMesh(void)
{
  return std::make_shared<Mesh>("BUILTIN_plane", vertices, 4, indices, 6);
}
