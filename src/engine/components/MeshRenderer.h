//
//  Author: Shervin Aflatooni
//

#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "../Component.h"
#include "../Mesh.h"
#include "../Material.h"

class MeshRenderer : public Component
{
public:
  MeshRenderer(Mesh *mesh, Material *material);
  virtual ~MeshRenderer(void);

  virtual void update(int delta);
  virtual void render(Shader *shader);

  inline virtual const char *getType(void) { return "MESH_RENDERER"; }

private:
  Mesh *mesh;
  Material *material;
};

#endif
