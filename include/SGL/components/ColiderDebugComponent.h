#ifndef WIREFRAME_H
#define WIREFRAME_H
#include <SGL/component.h>

namespace SGL::Components {


class ColiderDebugComponent : public Component
{
public:
    SGL::GameObject *parentObject = nullptr; 
    ColiderDebugComponent(SGL::GameObject* object) : Component("WIREFRAME") {
        parentObject = object;
    }

   
    void Start() override {
    }

   
    void Update() override {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        gameObject->transform.setPosition(parentObject->transform.getPosition());
        gameObject->transform.setScaling(parentObject->transform.getScaling() * 1.0001f); // slightly larger to avoid z-fighting
        gameObject->transform.setRotation(parentObject->transform.getRotation());
    }   
};

} // namespace SGL::Components
#endif