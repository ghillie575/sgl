#ifndef RB_STATIC_H
#define RB_STATIC_H

#include <PxPhysicsAPI.h>
#include <SGL/component.h>

using namespace physx;

/**
 * @brief A component representing a static rigid body in the physics simulation.
 * 
 * This component initializes a static rigid body using PhysX and attaches it to the game object.
 * Static rigid bodies do not move and are typically used for immovable objects like walls or floors.
 */
class RBStatic : public SGL::Component
{
private:
    // No private members for now.
public:
    /**
     * @brief Constructor for RBStatic.
     * 
     * Initializes the component with the name "RB_STATIC".
     */
    RBStatic() : Component("RB_STATIC") {}

    /**
     * @brief Called when the component is initialized.
     * 
     * Sets up the static rigid body for the game object, including its transform, material properties,
     * and physics actor. The rotation is converted from degrees to radians and applied in ZYX order.
     */
    void Start() override
    {
        // Convert degrees to radians for rotation.
        float degToRad = PxPi / 180.0f;

        // Extract rotation values from the game object's transform.
        float x = gameObject->transform.rotation.x * degToRad;
        float y = gameObject->transform.rotation.y * degToRad;
        float z = gameObject->transform.rotation.z * degToRad;

        // Apply intrinsic rotations in ZYX order (common for local space).
        PxQuat qx(x, PxVec3(1, 0, 0));
        PxQuat qy(y, PxVec3(0, 1, 0));
        PxQuat qz(z, PxVec3(0, 0, 1));

        // Combine rotations in the correct order.
        PxQuat q = qz * qy * qx;

        // Create a PhysX transform using the position and rotation of the game object.
        PxTransform transform = PxTransform(
            PxVec3(gameObject->transform.position.x, gameObject->transform.position.y, gameObject->transform.position.z),
            q);

        // Enable physics processing for the game object's physics object.
        gameObject->physObject->processPhysics = true;

        // Retrieve the physical properties of the game object.
        SGL::PhysProperties *properties = &gameObject->physObject->properties;

        // Create a PhysX material using the static friction, dynamic friction, and restitution values.
        PxMaterial *material = gameObject->window->physicsWorld->gPhysics->createMaterial(
            properties->staticFriction, properties->dynamicFriction, properties->restitution);

        // Set the friction combine mode to maximum.
        material->setFrictionCombineMode(PxCombineMode::eMAX);

        // Create a static rigid body actor and attach it to the game object's physics object.
        gameObject->physObject->actor = PxCreateStatic(
            *(gameObject->window->physicsWorld->gPhysics), transform, *gameObject->physObject->geometry, *material);
    }

    /**
     * @brief Called every frame to update the component.
     * 
     * Currently, this method does nothing for static rigid bodies.
     */
    void Update() override
    {
    }
};

#endif