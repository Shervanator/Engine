#ifndef VISIBLE_OBJECT_H
#define VISIBLE_OBJECT_H

#include "GameObject.h"
#include "Mesh.h"
#include "Texture.h"

class VisibleObject : public GameObject
{
public:
  VisibleObject(Mesh *mesh, Texture *texture);
  virtual ~VisibleObject(void);

  virtual void update(int delta);
  virtual void render(Shader *shader);

private:
  Mesh *mesh;
  Texture *texture;
};

#endif
