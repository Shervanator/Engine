#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <vector>

#include "GameObject.h"

class SceneNode
{
public:
  SceneNode(void);
  ~SceneNode(void);

  void addChild(SceneNode* child);
  void addObject(GameObject* object);

  void update(int delta);
  void render(void);

private:
  std::vector<SceneNode*> children;
  std::vector<GameObject*> gameObjects;
};

#endif
