//
//  Author: Shervin Aflatooni
//

#pragma once

#include <btBulletDynamicsCommon.h>
#include "../Component.h"

class BoxCollider : public Component
{
public:
  BoxCollider(const glm::vec3& size, float mass);
  virtual ~BoxCollider(void);

  virtual void registerWithEngine(Engine *engine);
  virtual void deregisterFromEngine(Engine *engine);
  virtual void update(std::chrono::microseconds delta);

  inline virtual const char *getType(void) { return "BULLET"; };

private:
  btRigidBody* m_body;
  btDefaultMotionState* m_myMotionState;
  btCollisionShape* m_groundShape;
};
