#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <vector>

#include "GameObject.h"
#include "Shader.h"

class SceneNode
{
public:
  SceneNode(void);
  ~SceneNode(void);

  void addChild(SceneNode* child);
  void addObject(GameObject* object);

  void updateAll(int delta);
  void renderAll(Shader *shader);

private:
  std::vector<SceneNode*> children;
  std::vector<GameObject*> gameObjects;
};

#endif
