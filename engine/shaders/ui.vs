#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out mat4 vertexColor;

uniform vec3 model;
uniform vec4 color;

void main()
{
	gl_Position = vec4(transform,1.0) * vec4(aPos, 1.0);
    vertexColor = color;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}