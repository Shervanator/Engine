//
//  Author: Shervin Aflatooni
//

#ifndef PLANE_H
#define PLANE_H

#include "Mesh.h"

class Plane
{
public:
  Plane(void);
  ~Plane(void);

  Mesh *getMesh(void);

private:
  Mesh *mesh;
};

#endif
