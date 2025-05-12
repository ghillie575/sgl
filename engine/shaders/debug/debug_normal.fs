#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos; 
void main()
{
   vec3 adjustedNormal = abs(Normal);
    FragColor = vec4(adjustedNormal, 1.0);
}