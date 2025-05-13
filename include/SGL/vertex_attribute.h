#include <string>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#ifndef SGL_VERTEX_ATTRIBUTE_H
#define SGL_VERTEX_ATTRIBUTE_H
namespace SGL
{
    class VertexAttribute
    {
    public:
        VertexAttribute() = default;
        VertexAttribute(int size, int location)
            : size(size), location(location) {}

        int size;
        int location;
        nlohmann::json toJson()
        {
            nlohmann::json json;
            json["size"] = size;
            json["location"] = location;
            return json;
        }
        void fromJson(const nlohmann::json &json)
        {
            if (json.contains("size"))
            {
                size = json["size"].get<int>();
            }
            if (json.contains("location"))
            {
                location = json["location"].get<int>();
            }
        }
    };
}
#endif // SGL_VERTEX_ATTRIBUTE_H