#ifndef BOX_COLIDER_H
#define BOX_COLIDER_H
#include <PxPhysicsAPI.h>
#include <SGL/component.h>
using namespace physx;
class BoxColider : public SGL::Component
{
    public:
    BoxColider() : Component("COLIDER_BOX") {}
    void prepare() override
    {
        PxVec3 size = PxVec3(gameObject->transform.scaling.x, gameObject->transform.scaling.y, gameObject->transform.scaling.z);
        PxBoxGeometry *boxGeometry = new PxBoxGeometry(size);
        gameObject->physObject->setGeometry(boxGeometry);
        std::cout << "BoxColider: " << gameObject->id << " created with size: " << size.x << ", " << size.y << ", " << size.z << std::endl;

    }
    void Start() override
    {
       
    }
    void Update() override
    {
    }
};
#endif