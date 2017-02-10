//
//  Author: Shervin Aflatooni
//

#include "BoxCollider.h"
#include "../Engine.h"
#include "../Transform.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

BoxCollider::BoxCollider(const glm::vec3& size, float mass)
{
  m_groundShape = new btBoxShape(btVector3(size.x, size.y, size.z));
  //m_groundShape = new btSphereShape(size.x);


  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0, 0, 0);
  if (isDynamic)
    m_groundShape->calculateLocalInertia(mass, localInertia);

  m_myMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape, localInertia);
  m_body = new btRigidBody(rbInfo);
  //m_body->applyTorque(btVector3(10, 3, 5));
}

BoxCollider::~BoxCollider(void)
{
  delete m_myMotionState;
  delete m_body;
  delete m_groundShape;
}

void BoxCollider::update(std::chrono::microseconds delta) {
  btTransform trans;
  if (m_body && m_body->getMotionState())
  {
    m_body->getMotionState()->getWorldTransform(trans);
    glm::mat4 test;
    trans.getOpenGLMatrix(glm::value_ptr(test));
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(test, scale, rotation, translation, skew, perspective);

    m_parentEntity->getTransform().setPosition(translation);
    m_parentEntity->getTransform().setRotation(glm::quat(rotation.w, -rotation.x, -rotation.y, -rotation.z));
  }
};

void BoxCollider::registerWithEngine(Engine *engine)
{
  auto pos = m_parentEntity->getPosition();
  auto rot = m_parentEntity->getTransform().getRotation();
  m_body->setWorldTransform(btTransform(btQuaternion(-rot.x, -rot.y, -rot.z, rot.w), btVector3(pos.x, pos.y, pos.z)));
  engine->getPhysicsManager()->registerCollider2(m_body);
}

void BoxCollider::deregisterFromEngine(Engine *engine)
{
  engine->getPhysicsManager()->deregisterCollider2(m_body);
}
