#version 330 core
out vec4 FragColor;
  
uniform sampler2D texture1;
uniform vec3 lightColor;
void main()
{
     FragColor = vec4(lightColor,1.0);
}