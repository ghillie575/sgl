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
        PxTransform transform = PxTransform(
            PxVec3(gameObject->transform.position.x, gameObject->transform.position.y, gameObject->transform.position.z),
            PxQuat(gameObject->transform.rotation.x, gameObject->transform.rotation.y, gameObject->transform.rotation.z, 1.0f).getNormalized()
        );
        gameObject->physObject->processPhysics = true;
        gameObject->physObject->actor = PxCreateStatic(*(gameObject->window->physicsWorld->gPhysics), transform, *gameObject->physObject->geometry, *gameObject->window->physicsWorld->gPhysics->createMaterial(0.5f, 0.5f, 0.0f));
    }
    void Update() override
    {
    }
};
#endif