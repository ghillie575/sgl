
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <cstring>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <SGL/shader.h>
#include <SGL/window.h>

using namespace SGL;
class DebugWindow
{
public:
    std::string textFragmentShader = R"(
#version 330 core
in vec2 TexCoords;
out vec4 color;
uniform sampler2D text;
uniform vec3 textColor;
void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}
)";
    std::string textVertexShader = R"(
#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;
uniform mat4 projection;
void main() {
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}
)";

    // Structs
    struct Character
    {
        unsigned int TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        unsigned int Advance;
    };
    struct Font
    {
        std::map<GLchar, Character> Characters;
    };

    std::map<std::string, Font> fonts;
    unsigned int VAO, VBO;

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    // Function Declarations

    // Main Debug Window
    int start_debug_window()
    {
        glfwDestroyWindow(glfwGetCurrentContext());
        glfwTerminate();
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SGL Debug window", NULL, NULL);
        if (!window)
        {
            std::cerr << "Failed to create GLFW window\n";
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD\n";
            return -1;
        }

        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        Shader shader(textVertexShader.c_str(), textFragmentShader.c_str(), true);
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
        shader.use();
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Load fonts
        if (!loadFont("engine/fonts/console.ttf", "console"))
            return -1;
        if (!loadFont("engine/fonts/Azonix.ttf", "modern"))
            return -1;

        // Setup VAO/VBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Info text
        std::string sgl_ver_str = "SGL version: " + std::string(SGL_VERSION);
        std::string glfw_ver_str = "GLFW version: " + std::to_string(GLFW_VERSION_MAJOR) + "." + std::to_string(GLFW_VERSION_MINOR) + "." + std::to_string(GLFW_VERSION_REVISION);

        float scale = 0.4f;
        float y = 500.0f;
        float lineSpacing = 25.0f;

        while (!glfwWindowShouldClose(window))
        {
            processDebugInput(window);
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            RenderText(shader, sgl_ver_str, 5, 550, scale, glm::vec3((float)208 / (float)255, (float)17 / (float)255, (float)212 / (float)255), "console");
            RenderText(shader, glfw_ver_str, 5, 525, scale, glm::vec3((float)208 / (float)255, (float)17 / (float)255, (float)212 / (float)255), "console");
            RenderText(shader, "SGL", 700, 5, 1.0f, glm::vec3(0, 1, 1), "modern");
            std::stringstream msg;
            msg << "\n\nUsing PhysX version: " << PX_PHYSICS_VERSION_MAJOR << "." << PX_PHYSICS_VERSION_MINOR << "." << PX_PHYSICS_VERSION_BUGFIX << std::endl;
            msg << "OS: ";
#ifdef _WIN32
            msg << "Windows" << std::endl;
#else
#ifdef __APPLE__
            msg << "MacOS" << std::endl;
#else
            msg << "Linux" << std::endl;
#endif
#endif
            msg << "CPU Architecture: ";
#ifdef __x86_64__
            msg << "x64" << std::endl;
#else
            msg << "x86" << std::endl;
#endif
            msg << "GL: " << glGetString(GL_VERSION) << std::endl;
            msg << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
            msg << "OpenGL: " << glGetString(GL_RENDERER) << std::endl;
            msg << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl;
            msg << "\n"
                << std::endl;

            std::string msg_final = msg.str();
            std::istringstream stream(msg_final);
            std::string line;
            while (std::getline(stream, line))
            {
                RenderText(shader, line, 5, y, scale, glm::vec3((float)34 / (float)255, (float)227 / (float)255, (float)92 / (float)255), "console");
                y -= lineSpacing;
            }
            std::stringstream compile_msg;
            compile_msg << "Compile info:\n";
#if defined(_MSC_VER)
            compile_msg << "Compiler: MSVC " << _MSC_VER << "\n";
#elif defined(__clang__)
            compile_msg << "Compiler: Clang " << __clang_version__ << "\n";
#elif defined(__GNUC__)
            compile_msg << "Compiler: GCC " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << "\n";
#else
            compile_msg << "Compiler: Unknown\n";
#endif

            // C++ Standard
            compile_msg << "C++ Standard: C++" << __cplusplus << "\n";
            compile_msg << "Press enter to continue" << std::endl;
            std::string msg_compiler_final = compile_msg.str();
            std::istringstream stream1(msg_compiler_final);
            std::string line1;
            while (std::getline(stream1, line1))
            {
                RenderText(shader, line1, 5, y, scale, glm::vec3((float)232 / (float)255, (float)118 / (float)255, (float)42 / (float)255), "console");
                y -= lineSpacing;
            }
            y = 500.0f;
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        glfwDestroyWindow(window);
        return 0;
    }

    bool loadFont(const std::string &fontPath, const std::string &fontName)
    {
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {
            std::cerr << "ERROR::FREETYPE: Could not init FreeType Library\n";
            return false;
        }

        FT_Face face;
        if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
        {
            std::cerr << "ERROR::FREETYPE: Failed to load font: " << fontPath << "\n";
            return false;
        }

        FT_Set_Pixel_Sizes(face, 0, 48);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        Font font;
        for (unsigned char c = 0; c < 128; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cerr << "ERROR::FREETYPE: Failed to load Glyph\n";
                continue;
            }

            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                         face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                         face->glyph->bitmap.buffer);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)};
            font.Characters.insert({c, character});
        }
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        fonts[fontName] = font;
        return true;
    }

    void RenderText(Shader &shader, const std::string &text, float x, float y, float scale, glm::vec3 color, const std::string &fontName)
    {
        shader.use();
        glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        const auto &Characters = fonts[fontName].Characters;
        for (auto c = text.begin(); c != text.end(); ++c)
        {
            Character ch = Characters.at(*c);

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;

            float vertices[6][4] = {
                {xpos, ypos + h, 0.0f, 0.0f},
                {xpos, ypos, 0.0f, 1.0f},
                {xpos + w, ypos, 1.0f, 1.0f},

                {xpos, ypos + h, 0.0f, 0.0f},
                {xpos + w, ypos, 1.0f, 1.0f},
                {xpos + w, ypos + h, 1.0f, 0.0f}};

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glDrawArrays(GL_TRIANGLES, 0, 6);
            x += (ch.Advance >> 6) * scale;
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void processDebugInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
    void showDebugScreen()
    {
        start_debug_window();
    }
};
