#include "VisibleObject.h"

VisibleObject::VisibleObject(Mesh *mesh, Texture *texture)
{
  this->mesh = mesh;
  this->texture = texture;
}

VisibleObject::~VisibleObject(void)
{
  delete mesh;
  delete texture;
}

void VisibleObject::update(int delta)
{}

void VisibleObject::render(Shader *shader)
{
  shader->bind();
  texture->bind(0);
  mesh->render();
}
