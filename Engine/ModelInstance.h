#ifndef MODEL_INSTANCE_H
#define MODEL_INSTANCE_H

#include "ModelAsset.h"

class ModelInstance
{
public:
  ModelInstance(ModelAsset *asset);
  ~ModelInstance(void);
private:
  ModelAsset *asset;
};

#endif
