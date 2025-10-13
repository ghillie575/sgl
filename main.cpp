#include <sgl/window.h>
#include <sgl/logger.h>
#include <sgl/utils.h>
#include <iostream>
int main() {
    Window window(800, 600, "SGl");
    if (window.init() != 0) {
        std::cerr << "Failed to initialize window" << std::endl;
        return -1;
    }
    //make sure required resources are loaded
    require("default_vs", ResourceType::RESOURCE_SHADER);
    window.start();
    window.cleanup();
    return 0;
}
