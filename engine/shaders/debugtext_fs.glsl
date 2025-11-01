//<<sgl.shader.loader=1.0;type=fragment;path=engine/shaders/debug_text_fs.glsl;name=debug_text;>>//
#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    float alpha = texture(text, TexCoords).r;
    FragColor = vec4(vec3(1.0,1.0,1.0), alpha);
}
