#ifndef DEBUG_COMPONENT_H
#define DEBUG_COMPONENT_H

#include "../EntityComponent.h"

#include "../Box.h"

class DebugComponent : public EntityComponent
{
public:
  DebugComponent(void);
  ~DebugComponent(void);

  virtual void render(Shader *shader);

private:
  Box *box;
};

#endif
