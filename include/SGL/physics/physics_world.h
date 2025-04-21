#ifndef PHYSWORLD_H
#define PHYSWORLD_H
#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>
namespace SGL
{
    using namespace physx;
    class PhysicsWorld
    {
    private:
        static PxDefaultAllocator gAllocator;
        static PxDefaultErrorCallback gErrorCallback;

        PxFoundation *gFoundation = nullptr;
        PxDefaultCpuDispatcher *gDispatcher = nullptr;

    public:
        PxPhysics *gPhysics = nullptr;
        PxScene *gScene = nullptr;
        void initializePhysics();
        PhysicsWorld();
        ~PhysicsWorld();
        bool processPhysics = true;
        void step(float deltaTime);
        void addBody(physx::PxActor *body);
        void removeBody(physx::PxActor *body);
        void setGravity(const glm::vec3 &gravity);
    };
}
#endif