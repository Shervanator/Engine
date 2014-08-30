#include "MeshRenderer.h"
#include <iostream>

MeshRenderer::MeshRenderer(Mesh *mesh, Texture *texture)
{
  this->mesh = mesh;
  this->texture = texture;
}

MeshRenderer::~MeshRenderer(void)
{
  delete mesh;
  delete texture;
}

void MeshRenderer::update(int delta)
{}

void MeshRenderer::render(Shader *shader)
{
  shader->bind();
  glUniformMatrix4fv(shader->getUniformLocation("Model", 1), 1, GL_FALSE, &(parentEntity->getWorldMatrix())[0][0]);

  texture->bind(0);
  mesh->render();
}
