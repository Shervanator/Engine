//
//  Author: Shervin Aflatooni
//

#pragma once

#include "Entity.h"
#include "Ray.h"

#include <vector>
#include <chrono>

#include <btBulletDynamicsCommon.h>

class PhysicsManager
{
public:
  PhysicsManager(void);
  ~PhysicsManager(void);

  void registerCollider(btRigidBody *rigidBody);
  void deregisterCollider(btRigidBody *rigidBody);

  void tick(std::chrono::microseconds delta);

  Entity *pick(Ray *ray) const;

private:
  btDefaultCollisionConfiguration *m_collisionConfiguration;
  btCollisionDispatcher *m_dispatcher;
  btBroadphaseInterface *m_overlappingPairCache;
  btSequentialImpulseConstraintSolver *m_solver;
  btDiscreteDynamicsWorld *m_dynamicsWorld;
};
