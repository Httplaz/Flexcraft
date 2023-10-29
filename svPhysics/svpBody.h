#pragma once
#include <bullet/btBulletDynamicsCommon.h>
#include <memory>

class svpBody {
public:
    svpBody(btCollisionShape* shape, float mass, const btVector3& position = btVector3(0, 0, 0));
    ~svpBody();

    void applyForce(const btVector3& force, const btVector3& rel_pos);
    void applyTorque(const btVector3& torque);

    btRigidBody* getBody() const;

private:
    std::unique_ptr<btMotionState> motionState;
    std::unique_ptr<btRigidBody> body;
};
