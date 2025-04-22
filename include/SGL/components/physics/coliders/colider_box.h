#ifndef BOX_COLIDER_H
#define BOX_COLIDER_H

#include <PxPhysicsAPI.h>
#include <SGL/component.h>

using namespace physx;

/**
 * @brief A class representing a box collider component in the physics system.
 * 
 * This class is responsible for creating and managing a box collider for a game object.
 * It inherits from the SGL::Component base class and overrides necessary methods.
 */
class BoxColider : public SGL::Component
{
public:
    /**
     * @brief Constructor for the BoxColider class.
     * 
     * Initializes the component with the name "COLIDER_BOX".
     */
    BoxColider() : Component("COLIDER_BOX") {}

    /**
     * @brief Prepares the box collider for the game object.
     * 
     * This method creates a PxBoxGeometry based on the scaling of the game object's transform
     * and sets it as the geometry for the associated physics object.
     */
    void prepare() override
    {
        // Create a PxVec3 representing the size of the box based on the game object's scaling.
        PxVec3 size = PxVec3(gameObject->transform.scaling.x, gameObject->transform.scaling.y, gameObject->transform.scaling.z);

        // Create a new PxBoxGeometry with the calculated size.
        PxBoxGeometry *boxGeometry = new PxBoxGeometry(size);

        // Set the geometry for the game object's physics object.
        gameObject->physObject->setGeometry(boxGeometry);

        // Log the creation of the box collider with its size.
        std::cout << "BoxColider: " << gameObject->id << " created with size: " << size.x << ", " << size.y << ", " << size.z << std::endl;
    }

    /**
     * @brief Called when the component starts.
     * 
     * This method is currently empty but can be overridden for initialization logic.
     */
    void Start() override
    {
    }

    /**
     * @brief Called every frame to update the component.
     * 
     * This method is currently empty but can be overridden for update logic.
     */
    void Update() override
    {
    }
};

#endif