#ifndef SGL_ERROR_HANDLER_H
#define SGL_ERROR_HANDLER_H
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
namespace SGL
{

    void handle_error(std::string error_message);
   
}
#endif