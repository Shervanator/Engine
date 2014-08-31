#ifndef BOX_H
#define BOX_H

#include "Mesh.h"

class Box
{
public:
  Box(void);
  ~Box(void);

  void render(void);

private:
  Mesh *mesh;
};

#endif
