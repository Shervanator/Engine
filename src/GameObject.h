#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Shader.h"
#include "Transform.h"

class SceneNode;

class GameObject
{
public:
  virtual ~GameObject(void) {};

  virtual void update(int delta) = 0;
  virtual void render(Shader *shader) = 0;

  glm::mat4 getTransformMatrix(void);
  Transform& getTransform(void);

  SceneNode *parentNode;

private:
  Transform transform;
};

#endif
