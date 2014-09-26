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
  shader->setUniformMatrix4f("World", parentEntity->getWorldMatrix());

  material->bind();
  mesh->render();
}
