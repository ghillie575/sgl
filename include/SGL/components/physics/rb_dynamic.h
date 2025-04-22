#ifndef RB_DYNAMIC_H
#define RB_DYNAMIC_H
#include <PxPhysicsAPI.h>
#include <SGL/component.h>
using namespace physx;
class RBDynamic : public SGL::Component
{
private:
public:
    RBDynamic() : Component("RB_DYNAMIC") {}
    void addForce(glm::vec3 force)
    {
        if (gameObject->physObject->actor)
        {
            static_cast<PxRigidDynamic *>(gameObject->physObject->actor)->addForce(PxVec3(force.x, force.y, force.z), PxForceMode::eFORCE);
        }
    }
    void addImpulse(glm::vec3 impulse)
    {
        if (gameObject->physObject->actor)
        {
            static_cast<PxRigidDynamic *>(gameObject->physObject->actor)->addForce(PxVec3(impulse.x, impulse.y, impulse.z), PxForceMode::eIMPULSE);
        }
    }
    void addTorque(glm::vec3 torque)
    {
        if (gameObject->physObject->actor)
        {
            static_cast<PxRigidDynamic *>(gameObject->physObject->actor)->addTorque(PxVec3(torque.x, torque.y, torque.z), PxForceMode::eFORCE);
        }
    }
    void stopMovement()
    {
        if (gameObject->physObject->actor)
        {
            PxRigidDynamic *actor = static_cast<PxRigidDynamic *>(gameObject->physObject->actor);

            // Set linear and angular velocities to zero
            actor->setLinearVelocity(PxVec3(0.0f, 0.0f, 0.0f));
            actor->setAngularVelocity(PxVec3(0.0f, 0.0f, 0.0f));
            actor->setForceAndTorque(PxVec3(0.0f, 0.0f, 0.0f), PxVec3(0.0f, 0.0f, 0.0f));
        }
    }

    void Start() override
    {
        float degToRad = PxPi / 180.0f;

        // Apply 45 by 45 by 45 degrees rotation
        float x = transform->position.x * degToRad;
        float y = transform->position.y * degToRad;
        float z = transform->position.z * degToRad;

        // Apply intrinsic rotations in ZYX order (common for local space)
        PxQuat qx(x, PxVec3(1, 0, 0));
        PxQuat qy(y, PxVec3(0, 1, 0));
        PxQuat qz(z, PxVec3(0, 0, 1));

        PxQuat q = qz * qy * qx; // Rotation order matters!

        PxTransform transform = PxTransform(
            PxVec3(gameObject->transform.position.x, gameObject->transform.position.y, gameObject->transform.position.z),
            q);

        // Handle other geometry types as needed
        gameObject->physObject->processPhysics = true;
        SGL::PhysProperties *properties = &gameObject->physObject->properties;
        PxMaterial *material = gameObject->window->physicsWorld->gPhysics->createMaterial(properties->staticFriction, properties->dynamicFriction, properties->restitution);
        material->setFrictionCombineMode(PxCombineMode::eMAX);
        PxRigidDynamic *actor = PxCreateDynamic(*(gameObject->window->physicsWorld->gPhysics), transform, *gameObject->physObject->geometry, *material, 1.0f);
        PxRigidBodyExt::updateMassAndInertia(*actor, properties->mass);
        actor->setAngularDamping(0.05f);                                               // Optional: Adjust to control rotational resistance
        actor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, properties->isKinematic); // Ensure it's not kinematic
        gameObject->physObject->actor = actor;
    }
    void Update() override
    {
    }
};
#endif