#ifndef PHYSPROPERTIES_H
#define PHYSPROPERTIES_H
#include <PxPhysicsAPI.h>
#include <nlohmann/json.hpp>
namespace SGL
{
    class PhysProperties
    {
    public:
        float mass = 10;
        float staticFriction = 0.8;
        float dynamicFriction = 0.8;
        float restitution = 0.0;
        bool isKinematic = false;
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