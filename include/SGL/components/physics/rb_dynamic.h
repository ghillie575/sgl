#ifndef RB_DYNAMIC_H
#define RB_DYNAMIC_H

#include <PxPhysicsAPI.h>
#include <SGL/component.h>

using namespace physx;

/**
 * @brief A component representing a dynamic rigid body in the physics simulation.
 * 
 * This component allows applying forces, impulses, and torques to a dynamic rigid body,
 * as well as stopping its movement. It also initializes the physics actor during the
 * Start phase of the game object's lifecycle.
 */
class RBDynamic : public SGL::Component
{
private:
    // No private members for now
public:
    /**
     * @brief Constructor for the RBDynamic component.
     */
    RBDynamic() : Component("RB_DYNAMIC") {}

    /**
     * @brief Applies a force to the rigid body.
     * 
     * @param force The force vector to apply.
     */
    void addForce(glm::vec3 force)
    {
        if (gameObject->physObject->actor)
        {
            static_cast<PxRigidDynamic *>(gameObject->physObject->actor)->addForce(PxVec3(force.x, force.y, force.z), PxForceMode::eFORCE);
        }
    }

    /**
     * @brief Applies an impulse to the rigid body.
     * 
     * @param impulse The impulse vector to apply.
     */
    void addImpulse(glm::vec3 impulse)
    {
        if (gameObject->physObject->actor)
        {
            static_cast<PxRigidDynamic *>(gameObject->physObject->actor)->addForce(PxVec3(impulse.x, impulse.y, impulse.z), PxForceMode::eIMPULSE);
        }
    }

    /**
     * @brief Applies a torque to the rigid body.
     * 
     * @param torque The torque vector to apply.
     */
    void addTorque(glm::vec3 torque)
    {
        if (gameObject->physObject->actor)
        {
            static_cast<PxRigidDynamic *>(gameObject->physObject->actor)->addTorque(PxVec3(torque.x, torque.y, torque.z), PxForceMode::eFORCE);
        }
    }

    /**
     * @brief Stops all movement of the rigid body.
     * 
     * Sets the linear and angular velocities to zero and clears any applied forces or torques.
     */
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

    /**
     * @brief Initializes the physics actor for the game object.
     * 
     * This method is called during the Start phase of the game object's lifecycle.
     * It sets up the physics actor with the appropriate transform, geometry, and material properties.
     */
    void Start() override
    {
        float degToRad = PxPi / 180.0f;

        // Convert position to radians for rotation
        float x = transform->position.x * degToRad;
        float y = transform->position.y * degToRad;
        float z = transform->position.z * degToRad;

        // Apply intrinsic rotations in ZYX order (common for local space)
        PxQuat qx(x, PxVec3(1, 0, 0));
        PxQuat qy(y, PxVec3(0, 1, 0));
        PxQuat qz(z, PxVec3(0, 0, 1));

        PxQuat q = qz * qy * qx; // Rotation order matters!

        // Create the transform for the physics actor
        PxTransform transform = PxTransform(
            PxVec3(gameObject->transform.position.x, gameObject->transform.position.y, gameObject->transform.position.z),
            q);

        // Enable physics processing for the game object
        gameObject->physObject->processPhysics = true;

        // Retrieve physics properties and create a material
        SGL::PhysProperties *properties = &gameObject->physObject->properties;
        PxMaterial *material = gameObject->window->physicsWorld->gPhysics->createMaterial(properties->staticFriction, properties->dynamicFriction, properties->restitution);
        material->setFrictionCombineMode(PxCombineMode::eMAX);

        // Create the dynamic rigid body actor
        PxRigidDynamic *actor = PxCreateDynamic(*(gameObject->window->physicsWorld->gPhysics), transform, *gameObject->physObject->geometry, *material, 1.0f);

        // Update mass and inertia
        PxRigidBodyExt::updateMassAndInertia(*actor, properties->mass);

        // Set angular damping and kinematic flag
        actor->setAngularDamping(0.05f);                                               // Optional: Adjust to control rotational resistance
        actor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, properties->isKinematic); // Ensure it's not kinematic

        // Assign the actor to the game object's physics object
        gameObject->physObject->actor = actor;
    }

    /**
     * @brief Updates the component every frame.
     * 
     * Currently, this method does nothing but can be extended for custom behavior.
     */
    void Update() override
    {
    }
};

#endif