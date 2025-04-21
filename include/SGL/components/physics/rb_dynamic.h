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
    void Start() override
    {
        PxTransform transform = PxTransform(
            PxVec3(gameObject->transform.position.x, gameObject->transform.position.y, gameObject->transform.position.z),
            PxQuat(gameObject->transform.rotation.x, gameObject->transform.rotation.y, gameObject->transform.rotation.z, 1.0f).getNormalized());

        // Handle other geometry types as needed
        gameObject->physObject->processPhysics = true;
        PxRigidDynamic *actor = PxCreateDynamic(*(gameObject->window->physicsWorld->gPhysics), transform, *gameObject->physObject->geometry, *gameObject->window->physicsWorld->gPhysics->createMaterial(0.5f, 0.5f, 0.0f), 1.0f);
        PxRigidBodyExt::updateMassAndInertia(*actor, 10.0f);
        actor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);   // ensure gravity is ON
        actor->setAngularDamping(0.05f);                             // Optional: Adjust to control rotational resistance
        actor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, false); // Ensure it's not kinematic
        actor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, false);
        actor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, false);
        actor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, false);

        gameObject->physObject->actor = actor;
    }
    void Update() override
    {
    }
};
#endif