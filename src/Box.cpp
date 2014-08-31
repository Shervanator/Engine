#include "Box.h"

Box::Box(void)
{
  mesh = new Mesh(Asset("cube.obj"));
}

Box::~Box(void)
{
  delete mesh;
}

void Box::render(void)
{
  mesh->render();
}
