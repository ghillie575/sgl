#ifndef PHYSWORLD_H
#define PHYSWORLD_H

#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>

namespace SGL
{
    using namespace physx;

    /**
     * @brief Represents the physics world, managing the physics simulation and related resources.
     */
    class PhysicsWorld
    {
    private:
        /**
         * @brief Default allocator for PhysX.
         */
        static PxDefaultAllocator gAllocator;

        /**
         * @brief Default error callback for PhysX.
         */
        static PxDefaultErrorCallback gErrorCallback;

        /**
         * @brief Foundation object for PhysX, required for initialization.
         */
        PxFoundation *gFoundation = nullptr;

        /**
         * @brief CPU dispatcher for PhysX tasks.
         */
        PxDefaultCpuDispatcher *gDispatcher = nullptr;

    public:
        /**
         * @brief Main physics object for PhysX.
         */
        PxPhysics *gPhysics = nullptr;

        /**
         * @brief Scene object representing the physics simulation.
         */
        PxScene *gScene = nullptr;

        /**
         * @brief Indicates whether the physics simulation should be processed.
         */
        bool processPhysics = true;

        /**
         * @brief Initializes the physics engine and sets up the necessary resources.
         */
        void initializePhysics();

        /**
         * @brief Constructor for the PhysicsWorld class.
         */
        PhysicsWorld();

        /**
         * @brief Destructor for the PhysicsWorld class. Cleans up resources.
         */
        ~PhysicsWorld();

        /**
         * @brief Advances the physics simulation by a given time step.
         * @param deltaTime The time step to advance the simulation by.
         */
        void step(float deltaTime);

        /**
         * @brief Adds a physics body (actor) to the simulation.
         * @param body The physics actor to add.
         */
        void addBody(physx::PxActor *body);

        /**
         * @brief Removes a physics body (actor) from the simulation.
         * @param body The physics actor to remove.
         */
        void removeBody(physx::PxActor *body);

        /**
         * @brief Sets the gravity vector for the physics simulation.
         * @param gravity A 3D vector representing the gravity direction and magnitude.
         */
        void setGravity(const glm::vec3 &gravity);
    };
}

#endif