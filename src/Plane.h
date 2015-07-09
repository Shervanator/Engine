//
//  Author: Shervin Aflatooni
//

#ifndef PLANE_H
#define PLANE_H

#include "Mesh.h"

class Plane
{
public:
  Plane(float width = 1, float height = 1);
  ~Plane(void);

  Mesh *getMesh(void);

private:
  Mesh *mesh;
};

#endif
