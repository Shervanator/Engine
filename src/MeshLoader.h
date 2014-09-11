#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "Entity.h"

#include <assimp/scene.h>

class MeshLoader
{
public:
  MeshLoader(const char* pFile);
  ~MeshLoader(void);

  Entity *getEntity(void);

private:
  void loadScene(const aiScene* scene);

  Entity *m_entity;
};

#endif
