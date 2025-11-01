//<<sgl.shader.loader=1.0;type=fragment;path=engine/shaders/default_fs.glsl;name=default_tex;>>//
#version 330 core
layout(location = 0) out vec4 outColor;
in vec2 TexCoord;

uniform sampler2D texture1;
void main()
{
    outColor = texture(texture1,TexCoord);
}