#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <vector>

#include "Shader.h"

#include "Transform.h"

class GameObject;

class SceneNode
{
public:
  SceneNode(void);
  ~SceneNode(void);

  void addChild(SceneNode* child);
  void addObject(GameObject* object);

  void updateAll(int delta);
  void renderAll(Shader *shader);

  Transform& getTransform(void);

  std::vector<SceneNode*> *getChildren(void);

  glm::mat4& getWorldMatrix(void);
private:
  Transform transform;

  SceneNode *parentNode;

  std::vector<SceneNode*> children;
  std::vector<GameObject*> gameObjects;

  glm::mat4 worldMatrix;
};

#endif
