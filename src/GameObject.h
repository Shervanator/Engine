#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Shader.h"
#include "SceneNode.h"

class GameObject
{
public:
  virtual ~GameObject(void) {};

  virtual void update(int delta) = 0;
  virtual void render(Shader *shader) {};

  void setParent(SceneNode *parentNode);

protected:
  SceneNode *parentNode;
};

#endif
