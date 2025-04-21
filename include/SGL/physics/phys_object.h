#ifndef PHYSOBJECT_H
#define PHYSOBJECT_H
#include <PxPhysicsAPI.h>
using namespace physx;
namespace SGL
{
    class Window;
    class PhysObject
    {
    private:
    public:
        PxGeometry *geometry;
        PxRigidActor *actor;
        bool processPhysics = false;
        PhysObject();
        ~PhysObject();
        PxGeometry *getGeometry();
        void setGeometry(PxGeometry *geometry);
        PxTransform getTransform();
        void setup(Window *window);
    };
}
#endif