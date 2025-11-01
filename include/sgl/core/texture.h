#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
enum ClampTypes
{
    CLAMP_REPEAT,
    CLAMP_MIRRORED_REPEAT,
    CLAMP_CLAMP_TO_EDGE,
    CLAMP_CLAMP_TO_BORDER
};
enum FilterTypes
{
    FILTER_NEAREST,
    FILTER_LINEAR
};
class Texture
{
public:
    unsigned int id;
    std::string path;
    int load(ClampTypes clampType, FilterTypes filterType);
    void bind();
};
#endif