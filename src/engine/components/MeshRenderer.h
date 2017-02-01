//
//  Author: Shervin Aflatooni
//

#pragma once

#include "../Component.h"
#include "../Mesh.h"
#include "../Material.h"

class MeshRenderer : public Component
{
public:
  MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
  virtual ~MeshRenderer(void);

  virtual void update(int delta);
  virtual void render(Shader *shader);

  inline virtual const char *getType(void) { return "MESH_RENDERER"; }

private:
  std::shared_ptr<Mesh> m_mesh;
  std::shared_ptr<Material> m_material;
};
