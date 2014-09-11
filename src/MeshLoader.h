#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "Asset.h"
#include "Entity.h"

#include <assimp/scene.h>

class MeshLoader
{
public:
  MeshLoader(Asset file);
  ~MeshLoader(void);

  Entity *getEntity(void);

private:
  void loadScene(const aiScene* scene);

  Entity *m_entity;
};

#endif
