#include "pch.h"

svpBody::svpBody(btCollisionShape* shape, float mass, const btVector3& position) {
    btVector3 localInertia(0, 0, 0);
    if (mass != 0.f)
        shape->calculateLocalInertia(mass, localInertia);

    motionState = std::make_unique<btDefaultMotionState>(btTransform(btQuaternion(0, 0, 0, 1), position));
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState.get(), shape, localInertia);
    body = std::make_unique<btRigidBody>(rbInfo);
}

svpBody::~svpBody() {
    delete body->getMotionState();
}

void svpBody::applyForce(const btVector3& force, const btVector3& rel_pos) {
    body->applyForce(force, rel_pos);
}

void svpBody::applyTorque(const btVector3& torque) {
    body->applyTorque(torque);
}

btRigidBody* svpBody::getBody() const {
    return body.get();
}
