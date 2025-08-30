#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <cstring>

#include <SGL/error_handler.h>
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
void SGL::handle_error(std::string error_message)
{
    fprintf(stderr, "Error: %s\n", error_message);
    std::string command = "./crashhandler \"" + error_message + "\"";
    system(command.c_str());
    exit(EXIT_FAILURE);
}
