#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>
enum ResourceType {
    RESOURCE_SHADER
};
void require(const std::string& name, ResourceType type);
#endif