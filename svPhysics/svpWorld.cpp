// svWorld.cpp
#include "pch.h"

svpWorld::svpWorld() {
    collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
    dispatcher = std::make_unique<btCollisionDispatcher>(collisionConfiguration.get());
    overlappingPairCache = std::make_unique<btDbvtBroadphase>();
    solver = std::make_unique<btSequentialImpulseConstraintSolver>();
    dynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(dispatcher.get(), overlappingPairCache.get(), solver.get(), collisionConfiguration.get());
}

svpWorld::~svpWorld() {
    for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if (body && body->getMotionState()) {
            delete body->getMotionState();
        }
        dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }
}

void svpWorld::addBody(svpBody body) {
    dynamicsWorld->addRigidBody(body.getBody());
}

void svpWorld::removeBody(svpBody body) {
    dynamicsWorld->removeRigidBody(body.getBody());
}

void svpWorld::simulate(float deltaTime) {
    dynamicsWorld->stepSimulation(deltaTime);
}
