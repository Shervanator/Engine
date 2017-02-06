//
//  Author: Shervin Aflatooni
//

#pragma once

#include "components/Sphere.h"
#include "Entity.h"
#include "Ray.h"

#include <vector>

#include <btBulletDynamicsCommon.h>

class PhysicsManager
{
public:
  PhysicsManager(void);
  ~PhysicsManager(void);

  void registerCollider(std::shared_ptr<Sphere> sphere);
  void registerCollider2(btRigidBody *rigidBody);
  void deregisterCollider(std::shared_ptr<Sphere> sphere);

  void tick(int delta);

  Entity *pick(Ray *ray) const;

private:
  std::vector<std::shared_ptr<Sphere>> m_colliders;

  btDefaultCollisionConfiguration* m_collisionConfiguration;
  btCollisionDispatcher* m_dispatcher;
  btBroadphaseInterface* m_overlappingPairCache;
  btSequentialImpulseConstraintSolver* m_solver;
  btDiscreteDynamicsWorld* m_dynamicsWorld;
};
