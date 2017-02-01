//
//  Author: Shervin Aflatooni
//

#pragma once

#include "Entity.h"
#include <string>

#include <assimp/scene.h>

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
};
