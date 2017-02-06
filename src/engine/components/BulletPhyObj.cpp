//
//  Author: Shervin Aflatooni
//

#include "BulletPhyObj.h"
#include "../Engine.h"
#include "../Transform.h"
#include <glm/gtc/type_ptr.hpp>
BulletPhyObj::BulletPhyObj(void)
{
  m_groundShape = new btBoxShape(btVector3(btScalar(50.),btScalar(50.),btScalar(50.)));

  btTransform groundTransform;
  groundTransform.setIdentity();
  groundTransform.setOrigin(btVector3(0,-56,0));

  btScalar mass(0.);

  //rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0,0,0);
  if (isDynamic)
    m_groundShape->calculateLocalInertia(mass,localInertia);

  //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
  m_myMotionState = new btDefaultMotionState(groundTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape, localInertia);
  m_body = new btRigidBody(rbInfo);

  //add the body to the dynamics world
  //dynamicsWorld->addRigidBody(m_body);
}

BulletPhyObj::~BulletPhyObj(void)
{
  // delete m_body;
  // delete m_myMotionState;
  // delete m_groundShape;
}

void BulletPhyObj::update(int delta) {
  btTransform trans;
  if (m_body && m_body->getMotionState())
  {
    m_body->getMotionState()->getWorldTransform(trans);
  }

  //trans.getOpenGLMatrix(glm::value_ptr(parentEntity->getTransform().m_position));
};

void BulletPhyObj::registerWithEngine(Engine *engine)
{
  engine->getPhysicsManager()->registerCollider2(m_body);
}

void BulletPhyObj::deregisterFromEngine(Engine *engine)
{
  //engine->getPhysicsManager()->deregisterCollider2();
}
