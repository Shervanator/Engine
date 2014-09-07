#ifndef PLANE_H
#define PLANE_H

#include "Mesh.h"
#include "EntityComponent.h"

class Plane : public EntityComponent
{
public:
  Plane(void);
  ~Plane(void);

  virtual void render(Shader *shader);

private:
  Mesh *mesh;
};

#endif
