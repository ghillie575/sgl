#include <SGL/window.h>
#include <SGL/object.h>

#include <SGL/logger.h>

class Triangle : public GameObject
{
public:
    void build() override
    {
        Logger logger = Logger("Triangle");
        logger.log(LogLevel::INFO, "Building Triangle object");
        GameObject::build(); // Call the base class build method
    }
    void render() override
    {
        
        GameObject::render(); // Call the base class render method
    }
};
extern "C"
{
    void onTypeRegister(Window* window)
    {
        window->factory.registerObject("triangle", []() { return std::make_shared<Triangle>(); });
    }
}