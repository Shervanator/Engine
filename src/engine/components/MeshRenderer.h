//
//  Author: Shervin Aflatooni
//

#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "../EntityComponent.h"
#include "../Mesh.h"
#include "../Material.h"

class MeshRenderer : public EntityComponent
{
public:
  MeshRenderer(Mesh *mesh, Material *material);
  virtual ~MeshRenderer(void);

  virtual void update(int delta);
  virtual void render(Shader *shader);

private:
  Mesh *mesh;
  Material *material;
};

#endif
