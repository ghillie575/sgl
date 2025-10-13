//<<sgl.shader.loader=1.0;type=fragment;path=engine/shaders/default_fs.glsl;name=default_vs;>>//
#version 330 core
layout(location = 0) out vec4 outColor;
void main()
{
    outColor = vec4(1.0, 1.0, 1.0, 1.0); // White color
}