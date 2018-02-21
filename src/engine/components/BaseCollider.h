//
//  Author: Shervin Aflatooni
//

#pragma once

#include <btBulletDynamicsCommon.h>
#include "../Component.h"

class BaseCollider : public Component
{
public:
  BaseCollider(btCollisionShape *shape, float mass);
  virtual ~BaseCollider(void);

  virtual void registerWithEngine(Engine *engine);
  virtual void deregisterFromEngine(Engine *engine);
  virtual void update(Input *input, std::chrono::microseconds delta);

  inline virtual const char *getType(void) { return "BASE_COLLIDER"; };

  void applyCentralImpulse(const glm::vec3 &impulse);

private:
  btRigidBody *m_body;
  btDefaultMotionState *m_myMotionState;
  btCollisionShape *m_shape;
};
