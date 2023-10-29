#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <memory>
#include "svpBody.h"

class svpWorld {
public:
    svpWorld();
    ~svpWorld();

    void addBody(svpBody body);
    void removeBody(svpBody body);
    void simulate(float deltaTime);

private:
    std::unique_ptr<btDefaultCollisionConfiguration> collisionConfiguration;
    std::unique_ptr<btCollisionDispatcher> dispatcher;
    std::unique_ptr<btBroadphaseInterface> overlappingPairCache;
    std::unique_ptr<btSequentialImpulseConstraintSolver> solver;
    std::unique_ptr<btDiscreteDynamicsWorld> dynamicsWorld;
};
