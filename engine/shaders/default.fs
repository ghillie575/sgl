#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;
uniform vec3 color;
uniform float ambientStrength;
uniform sampler2D texture1;
void main()
{
     FragColor = texture(texture1, TexCoord) * vec4(color, 1.0) * ambientStrength;
}