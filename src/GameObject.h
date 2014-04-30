#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Shader.h"
#include "Transform.h"

class GameObject
{
public:
  virtual ~GameObject(void) {};

  virtual void update(int delta) = 0;
  virtual void render(Shader *shader) = 0;

  inline Transform& getTransform(void) { return transform; };

private:
  Transform transform;
};

#endif
