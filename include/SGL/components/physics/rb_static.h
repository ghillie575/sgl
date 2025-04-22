#ifndef RB_STATIC_H
#define RB_STATIC_H
#include <PxPhysicsAPI.h>
#include <SGL/component.h>
using namespace physx;
class RBStatic : public SGL::Component
{
private:
public:
    RBStatic() : Component("RB_STATIC") {}
    void Start() override
    {
        float degToRad = PxPi / 180.0f;

        float x = gameObject->transform.rotation.x * degToRad;
        float y = gameObject->transform.rotation.y * degToRad;
        float z = gameObject->transform.rotation.z * degToRad;

        // Apply intrinsic rotations in ZYX order (common for local space)
        PxQuat qx(x, PxVec3(1, 0, 0));
        PxQuat qy(y, PxVec3(0, 1, 0));
        PxQuat qz(z, PxVec3(0, 0, 1));

        PxQuat q = qz * qy * qx; // Rotation order matters!
        PxTransform transform = PxTransform(
            PxVec3(gameObject->transform.position.x, gameObject->transform.position.y, gameObject->transform.position.z),
            q);
        gameObject->physObject->processPhysics = true;
        SGL::PhysProperties *properties = &gameObject->physObject->properties;
        PxMaterial *material = gameObject->window->physicsWorld->gPhysics->createMaterial(properties->staticFriction, properties->dynamicFriction, properties->restitution);
        material->setFrictionCombineMode(PxCombineMode::eMAX);
        gameObject->physObject->processPhysics = true;
        gameObject->physObject->actor = PxCreateStatic(*(gameObject->window->physicsWorld->gPhysics), transform, *gameObject->physObject->geometry, *material);
    }
    void Update() override
    {
    }
};
#endif