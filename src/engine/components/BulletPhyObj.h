//
//  Author: Shervin Aflatooni
//

#pragma once

#include <btBulletDynamicsCommon.h>
#include "../Component.h"

class BulletPhyObj : public Component
{
public:
  BulletPhyObj(void);
  virtual ~BulletPhyObj(void);

  virtual void registerWithEngine(Engine *engine);
  virtual void deregisterFromEngine(Engine *engine);
  virtual void update(int delta);

  inline virtual const char *getType(void) { return "BULLET"; };

private:
  btRigidBody* m_body;
  btDefaultMotionState* m_myMotionState;
  btCollisionShape* m_groundShape;
};
