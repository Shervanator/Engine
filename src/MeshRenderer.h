#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "EntityComponent.h"
#include "Mesh.h"
#include "Texture.h"

class MeshRenderer : public EntityComponent
{
public:
  MeshRenderer(Mesh *mesh, Texture *texture);
  virtual ~MeshRenderer(void);

  virtual void update(int delta);
  virtual void render(Shader *shader);

private:
  Mesh *mesh;
  Texture *texture;
};

#endif
