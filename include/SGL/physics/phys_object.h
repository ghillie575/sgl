#ifndef PHYSOBJECT_H
#define PHYSOBJECT_H

#include <PxPhysicsAPI.h>
#include <SGL/physics/phys_propreties.h>

using namespace physx;

namespace SGL
{
    class Window;

    /**
     * @brief Represents a physical object in the physics simulation.
     * 
     * This class encapsulates the geometry, actor, and physical properties
     * of an object, and provides methods to manipulate and retrieve its state.
     */
    class PhysObject
    {
    private:
        // Private members can be added here if needed in the future.

    public:
        PxGeometry *geometry; ///< Pointer to the geometry of the physical object.
        PxRigidActor *actor; ///< Pointer to the rigid actor representing the object in the physics simulation.
        PhysProperties properties; ///< Physical properties of the object (e.g., mass, friction).
        bool processPhysics = false; ///< Flag to determine if physics should be processed for this object.

        /**
         * @brief Default constructor for PhysObject.
         */
        PhysObject();

        /**
         * @brief Destructor for PhysObject.
         */
        ~PhysObject();

        /**
         * @brief Retrieves the geometry of the physical object.
         * @return Pointer to the PxGeometry of the object.
         */
        PxGeometry *getGeometry();

        /**
         * @brief Sets the geometry of the physical object.
         * @param geometry Pointer to the new PxGeometry to set.
         */
        void setGeometry(PxGeometry *geometry);

        /**
         * @brief Retrieves the current transform of the physical object.
         * @return PxTransform representing the object's position and orientation.
         */
        PxTransform getTransform();

        /**
         * @brief Sets up the physical object within the given window context.
         * @param window Pointer to the Window object where the physics simulation is running.
         */
        void setup(Window *window);
    };
}

#endif