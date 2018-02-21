//
//  Author: Shervin Aflatooni
//

#include "BaseCollider.h"
#include "../Engine.h"
#include "../Transform.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

BaseCollider::BaseCollider(btCollisionShape *shape, float mass)
{
  m_shape = shape;

  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0, 0, 0);
  if (isDynamic)
    m_shape->calculateLocalInertia(mass, localInertia);

  m_myMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_shape, localInertia);
  m_body = new btRigidBody(rbInfo);
}

BaseCollider::~BaseCollider(void)
{
  delete m_myMotionState;
  delete m_body;
  delete m_shape;
}

void BaseCollider::update(Input *input, std::chrono::microseconds delta)
{
  if (m_body && !m_body->isStaticObject() && m_body->getMotionState())
  {
    btTransform trans;
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

void BaseCollider::registerWithEngine(Engine *engine)
{
  auto pos = m_parentEntity->getPosition();
  auto rot = m_parentEntity->getTransform().getRotation();
  m_body->setWorldTransform(btTransform(btQuaternion(-rot.x, -rot.y, -rot.z, rot.w), btVector3(pos.x, pos.y, pos.z)));
  engine->getPhysicsManager()->registerCollider2(m_body);
}

void BaseCollider::deregisterFromEngine(Engine *engine)
{
  engine->getPhysicsManager()->deregisterCollider2(m_body);
}

void BaseCollider::applyCentralImpulse(const glm::vec3 &impulse)
{
  m_body->applyCentralImpulse(btVector3(impulse.x, impulse.y, impulse.z));
}
