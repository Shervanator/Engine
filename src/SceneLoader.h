//
//  Author: Shervin Aflatooni
//

#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H

#include "Entity.h"
#include "Mesh.h"
#include "Material.h"
#include "components/Camera.h"
#include <string>
#include <map>

#include <assimp/scene.h>

class SceneLoader
{
public:
  SceneLoader(const std::string file);
  ~SceneLoader(void);

  Entity *getEntity(void);
  Camera *getCamera(void);

private:
  void loadScene(const aiScene* scene);
  Mesh* loadMesh(const aiMesh* mesh);
  Material* loadMaterial(const aiMaterial* material);
  Entity* loadGraph(aiNode* node, Entity* parentEntity, const aiScene* scene);

  std::string m_fileName;

  Entity *m_entity;
  Camera *m_camera;

  std::map<std::string, aiNodeAnim *> m_nodeAnimation;
};

#endif
