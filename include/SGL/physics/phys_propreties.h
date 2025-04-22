#ifndef PHYSPROPERTIES_H
#define PHYSPROPERTIES_H

#include <PxPhysicsAPI.h>
#include <nlohmann/json.hpp>

namespace SGL
{
    /**
     * @brief A class representing the physical properties of an object.
     * 
     * This class encapsulates various physical properties such as mass, friction, restitution, 
     * and whether the object is kinematic. It also provides functionality to serialize and 
     * deserialize these properties to and from JSON.
     */
    class PhysProperties
    {
    public:
        float mass = 10; ///< The mass of the object (default: 10).
        float staticFriction = 0.8; ///< The static friction coefficient (default: 0.8).
        float dynamicFriction = 0.8; ///< The dynamic friction coefficient (default: 0.8).
        float restitution = 0.0; ///< The restitution (bounciness) of the object (default: 0.0).
        bool isKinematic = false; ///< Whether the object is kinematic (default: false).

        /**
         * @brief Serializes the physical properties to a JSON object.
         * 
         * @return A JSON object containing the serialized physical properties.
         */
        nlohmann::json toJson() const
        {
            nlohmann::json j;
            j["mass"] = mass;
            j["staticFriction"] = staticFriction;
            j["dynamicFriction"] = dynamicFriction;
            j["restitution"] = restitution;
            j["isKinematic"] = isKinematic;
            return j;   
        }

        /**
         * @brief Deserializes the physical properties from a JSON object.
         * 
         * @param j A JSON object containing the physical properties.
         */
        void fromJson(const nlohmann::json &j)
        {
            j.at("mass").get_to(mass);
            j.at("staticFriction").get_to(staticFriction);
            j.at("dynamicFriction").get_to(dynamicFriction);
            j.at("restitution").get_to(restitution);
            j.at("isKinematic").get_to(isKinematic);
        }
    };
}

#endif