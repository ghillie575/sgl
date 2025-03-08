#ifndef BASIC_MATERIALS_H

#include <SGL/material.h>

namespace SGL
{
    Material basicPlasticMaterial()
    {

        Material m = Material();
        m.specular = glm::vec3(0.5f, 0.5f, 0.5f);
        m.shininess = 32.0f;
        return m;
    }
}
#define BASIC_MATERIALS_H
#endif // BASIC_MATERIALS_H