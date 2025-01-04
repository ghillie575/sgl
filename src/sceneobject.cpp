#include <sceneobject.h>
#include <random>
void SceneObject::fromJson(const nlohmann::json &json)
{
    if (json.contains("transform")) {
        transform.fromJson(json["transform"]);
    }
    if (json.contains("model")) {
        model = json["model"].get<std::string>();
    }
    if (json.contains("type")) {
        type = json["type"].get<std::string>();
    }
    if (json.contains("shader")) {
        shader = json["shader"];
    }
    if (json.contains("id")) {
        id = json["id"];
    }
    if (json.contains("name")) {
        name = json["name"];
    }
    if (json.contains("mode")) {
        if (json["mode"].dump().compare("ln") == 0) {
            mode = lines;
        } else if (json["mode"].dump().compare("trg") == 0) {
            mode = triangles;
        }
    }
}
SceneObject::SceneObject()
{
    this->id = generateRandomID(10);
}
void SceneObject::setObjectName(std::string name){
    this->name = name;
}
// Add toJson method to generate JSON data
nlohmann::json SceneObject::toJson() const
{
    nlohmann::json json;
    if (mode == lines)
    {
        json["mode"] = "ln";
    }
    else if (mode == triangles)
    {
        json["mode"] = "trg";
    }
    json["transform"] = transform.toJson();
    json["model"] = model;
    json["shader"] = shader;
    json["id"] = id;
    json["name"] = name;
    json["type"] = type;
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