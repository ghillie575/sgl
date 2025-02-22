#include <SGL/window.h>
#include <SGL/object.h>

#include <SGL/logger.h>
using namespace SGL;
class Triangle : public GameObject
{
public:
    void build() override
    {
        Logger logger = Logger("Triangle");
        logger.log(LogLevel::INFO, "Building Triangle object with ID: " + id);
        GameObject::build(); // Call the base class build method
    }
    void render(Window* window) override
    {
        GameObject::render(window); // Call the base class render method
    }
};
extern "C"
{
    void onTypeRegister(Window* window)
    {
        window->factory.registerObject("triangle", []() { return std::make_shared<Triangle>(); });
    }
}
extern "C"{
    LibInfo libInfo(){
        LibInfo info("ghillie575.sgl-objectlib-sample", "SGL Object Library Sample", LibType::OBJECT);;
        return info;
    }
}
