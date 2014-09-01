#include "MeshRenderer.h"
#include <iostream>

MeshRenderer::MeshRenderer(Mesh *mesh, Material *material)
{
  this->mesh = mesh;
  this->material = material;
}

MeshRenderer::~MeshRenderer(void)
{
  delete mesh;
  delete material;
}

void MeshRenderer::update(int delta)
{}

void MeshRenderer::render(Shader *shader)
{
  shader->bind();
  glUniformMatrix4fv(shader->getUniformLocation("World"), 1, GL_FALSE, &(parentEntity->getWorldMatrix())[0][0]);

  material->bind();
  mesh->render();
}
