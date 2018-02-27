//
//  Author: Shervin Aflatooni
//

#pragma once

#include "Material.h"
#include "Texture.h"
#include "Mesh.h"

#include "Entity.h"
#include <string>
#include <map>
#include <vector>

#include <assimp/scene.h>

struct MeshRendererData {
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;
};

class MeshLoader
{
public:
  MeshLoader(const std::string file);
  ~MeshLoader(void);

  std::shared_ptr<Entity> getEntity(void) const;

private:
  void loadScene(const aiScene* scene);

  std::string m_fileName;

  std::shared_ptr<Entity> m_entity;

  static std::map<std::string, std::vector<MeshRendererData>> sceneMeshRendererDataCache;
};
