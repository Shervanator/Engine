#ifndef MODEL_INSTANCE_H
#define MODEL_INSTANCE_H

#include "Mesh.h"

class ModelInstance
{
public:
  ModelInstance(Mesh *mesh);
  ~ModelInstance(void);
private:
  Mesh *mesh;
};

#endif
