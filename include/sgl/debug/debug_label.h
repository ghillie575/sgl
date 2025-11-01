#ifndef DEBUG_LABEL_H
#define DEBUG_LABEL_H
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sgl/core/shader.h>
#include <map>
struct Character
{
    unsigned int TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
};

class DebugLabel
{
public:
    DebugLabel(const std::string &text) : _text(text) {}
    void setText(const std::string &text) { _text = text; }
    std::string getText() const { return _text; }
    void render();
    int init();
    float x = 0;
    float y = 0;
    float scale = 1;

private:
    std::string _text;
    void RenderText(Shader &shader, std::string text, float x, float y, float scale);
    unsigned int VAO, VBO;
    Shader *shader;
    bool initialized = false;
    std::map<GLchar, Character> Characters;
};
#endif