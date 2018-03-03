//
//  Author: Shervin Aflatooni
//

#include "PhysicsManager.h"

#include <glm/gtx/norm.hpp>

#include <algorithm>

PhysicsManager::PhysicsManager(void)
{
  m_collisionConfiguration = new btDefaultCollisionConfiguration();
  m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
  m_overlappingPairCache = new btDbvtBroadphase();
  m_solver = new btSequentialImpulseConstraintSolver;
  m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver, m_collisionConfiguration);

  m_dynamicsWorld->setGravity(btVector3(0, -9.8, 0));
}

PhysicsManager::~PhysicsManager(void)
{
  delete m_dynamicsWorld;
  delete m_solver;
  delete m_overlappingPairCache;
  delete m_dispatcher;
  delete m_collisionConfiguration;
}
void PhysicsManager::registerCollider(btRigidBody *rigidBody)
{
  m_dynamicsWorld->addRigidBody(rigidBody);
}

void PhysicsManager::deregisterCollider(btRigidBody *rigidBody)
{
  m_dynamicsWorld->removeRigidBody(rigidBody);
}

void PhysicsManager::tick(std::chrono::microseconds delta)
{
  m_dynamicsWorld->stepSimulation(std::chrono::duration_cast<std::chrono::duration<float>>(delta).count());
}

Entity *PhysicsManager::pick(Ray *ray) const
{
  auto position = ray->getPosition();
  auto positionVec = btVector3(position.x, position.y, position.z);

  auto endPosition = ray->getEndPosition(1000.f);
  auto endPositionVec = btVector3(endPosition.x, endPosition.y, endPosition.z);

  btCollisionWorld::ClosestRayResultCallback rayCallback(positionVec, endPositionVec);

  m_dynamicsWorld->rayTest(positionVec, endPositionVec, rayCallback);

  if (rayCallback.hasHit())
  {
    return (Entity *)rayCallback.m_collisionObject->getUserPointer();
  }
  else
  {
    return nullptr;
  }
}
