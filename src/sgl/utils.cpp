#include <sgl/utils.h>
#include <sgl/logger.h>
#include <sgl/engine/shader_loader.h>
void require(const std::string& name, ResourceType type) {
    if (type == RESOURCE_SHADER) {
        if(loadShader(name) != 0) {
            getLogger()->error("REQUIRE", "Failed to load required shader: " + name);
            exit(EXIT_FAILURE);
        } else {
        }
    } else {
        getLogger()->warn("REQUIRE", "Unknown resource type requested");
    }
}