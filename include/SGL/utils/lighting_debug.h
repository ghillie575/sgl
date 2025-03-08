#ifndef LIGHTNING_DEBUG_H
#define LIGHTNING_DEBUG_H
#include <SGL/window.h>
namespace SGL{
    void visualizeLightSource(Window* window){
        std::shared_ptr<GameObject> obj = window->factory.createObject("default");
        obj->useShader("light");
        obj->loadModel("basic/3d/cube");
        obj->transform.setPosition(window->lightEnv.sunPos);
        obj->transform.setScaling(glm::vec3(0.3,0.3,0.3));
        window->registerObject(obj);
    }
}
#endif