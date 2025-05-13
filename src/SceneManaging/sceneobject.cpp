#include <SGL/SceneManaging/sceneobject.h>
#include <random>
using namespace SGL;
void SceneObject::fromJson(const nlohmann::json &json)
{
    if (json.contains("transform"))
    {
        transform.fromJson(json["transform"]);
    }
    if (json.contains("model"))
    {
        model = json["model"].get<std::string>();
    }
    if (json.contains("type"))
    {
        type = json["type"].get<std::string>();
    }
    if (json.contains("shader"))
    {
        shader = json["shader"];
    }
    if (json.contains("id"))
    {
        id = json["id"];
    }
    if (json.contains("name"))
    {
        name = json["name"];
    }
    if (json.contains("texture"))
    {
        texture = json["texture"];
    }
    if (json.contains("material"))
    {
        material.fromJson(json["material"]);
    }
    if (json.contains("components"))
    {
        for (const auto &componentJson : json.at("components"))
        {
            components.push_back(componentJson.get<std::string>());
        }
    }
    if (json.contains("physics"))
    {
        if (json["physics"].contains("properties"))
        {
            properties.fromJson(json["physics"]["properties"]);
        }
    }
    if(json.contains("vertexAttributes"))
    {
        for (const auto &attributeJson : json.at("vertexAttributes"))
        {
            VertexAttribute attribute;
            attribute.fromJson(attributeJson);
            vertexAttributes.push_back(attribute);
        }
    }
}
SceneObject::SceneObject()
{
    this->id = generateRandomID(10);
}
void SceneObject::setObjectName(std::string name)
{
    this->name = name;
}
// Add toJson method to generate JSON data
nlohmann::json SceneObject::toJson() const
{
    nlohmann::json json;
    json["transform"] = transform.toJson();
    json["material"] = material.toJson();
    json["physics"]["properties"] = properties.toJson();
    json["model"] = model;
    json["shader"] = shader;
    json["id"] = id;
    json["name"] = name;
    json["type"] = type;
    json["texture"] = texture;
    for (const auto &component : components)
    {
        json["components"].push_back(component);
    }
    json["vertexAttributes"] = nlohmann::json::array();
    for (auto attribute : vertexAttributes)
    {
        json["vertexAttributes"].push_back(attribute.toJson());
    }
    return json;
}
std::string SceneObject::generateRandomID(int length)
{
    // Create a random number generator
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator

    // Define the range for digits (0-9)
    std::uniform_int_distribution<> distr(0, 9);

    std::string id;
    for (int i = 0; i < length; ++i)
    {
        id += std::to_string(distr(eng)); // Generate a random digit and append to the ID
    }

    return id;
}
void SceneObject::addComponent(std::string type)
{
    components.push_back(type);
}
void SceneObject::addVertexAttribute(int size, int location)
{
    vertexAttributes.push_back(VertexAttribute(size, location));
}