#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <vector>

#include "GameObject.h"
#include "Shader.h"

#include "Transform.h"

class SceneNode
{
public:
  SceneNode(void);
  ~SceneNode(void);

  void addChild(SceneNode* child);
  void addObject(GameObject* object);

  void updateAll(int delta);
  void renderAll(Shader *shader);

  glm::mat4 getTransformMatrix(void);
  Transform& getTransform(void);

private:
  Transform transform;

  SceneNode *parentNode;

  std::vector<SceneNode*> children;
  std::vector<GameObject*> gameObjects;
};

#endif
