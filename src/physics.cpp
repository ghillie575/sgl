#include <SGL/physics/phys_object.h>
#include <PxPhysicsAPI.h> // Include PhysX API
#include <SGL/window.h>
#include <SGL/physics/physics_world.h>
using namespace physx;
namespace SGL
{
    PhysObject::PhysObject()
        : geometry(), actor(), processPhysics(true) {}

    PhysObject::~PhysObject()
    {
        if (geometry)
        {
            delete geometry;
            geometry = nullptr;
        }
        if (actor)
        {
            actor->release();
            actor = nullptr;
        }
    }

    PxGeometry *PhysObject::getGeometry()
    {
        return geometry;
    }

    void PhysObject::setGeometry(PxGeometry *newGeometry)
    {
        if (geometry)
        {
            delete geometry;
        }
        geometry = newGeometry;
    }

    PxTransform PhysObject::getTransform()
    {
        if (actor)
        {
            return actor->getGlobalPose();
        }
        return PxTransform(PxIdentity);
    }

    void PhysObject::setup(Window *window)
    {
            window->physicsWorld->addBody(actor);
    }
    // physworld
    PxDefaultAllocator PhysicsWorld::gAllocator;
    PxDefaultErrorCallback PhysicsWorld::gErrorCallback;

    PhysicsWorld::PhysicsWorld()
    {
    }

    PhysicsWorld::~PhysicsWorld()
    {
        if (gScene)
        {
            gScene->release();
            gScene = nullptr;
        }
        if (gDispatcher)
        {
            gDispatcher->release();
            gDispatcher = nullptr;
        }
        if (gPhysics)
        {
            gPhysics->release();
            gPhysics = nullptr;
        }
        if (gFoundation)
        {
            gFoundation->release();
            gFoundation = nullptr;
        }
    }

    void PhysicsWorld::initializePhysics()
    {
        gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
        gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale());

        PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
        sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
        gDispatcher = PxDefaultCpuDispatcherCreate(2);
        sceneDesc.cpuDispatcher = gDispatcher;
        sceneDesc.filterShader = PxDefaultSimulationFilterShader;
        gScene = gPhysics->createScene(sceneDesc);
    }

    void PhysicsWorld::step(float deltaTime)
    {
        if (processPhysics && gScene)
        {
            gScene->simulate(deltaTime);
            gScene->fetchResults(true);
        }
    }

    void PhysicsWorld::addBody(physx::PxActor *body)
    {
        if (gScene && body)
        {
            gScene->addActor(*body);
        }
    }

    void PhysicsWorld::removeBody(physx::PxActor *body)
    {
        if (gScene && body)
        {
            gScene->removeActor(*body);
        }
    }

    void PhysicsWorld::setGravity(const glm::vec3 &gravity)
    {
        if (gScene)
        {
            gScene->setGravity(PxVec3(gravity.x, gravity.y, gravity.z));
        }
    }
}