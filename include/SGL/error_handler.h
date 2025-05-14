#ifndef SGL_ERROR_HANDLER_H
#define SGL_ERROR_HANDLER_H
namespace SGL
{
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
    void handle_error(std::string error_message);
}
#endif