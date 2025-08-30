#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform float time;
float rand(vec3 co){
    return fract(sin(dot(co, vec3(12.9898, 78.233, 45.164))) * 43758.5453);
}
void main()
{
    // Vibrant, smoothly changing colors
    vec3 dynamicColor;
    dynamicColor.r = rand(vec3(FragPos.x * time, FragPos.y, FragPos.z));
    dynamicColor.g = rand(vec3(FragPos.x, FragPos.y * time * 1.3, FragPos.z));
    dynamicColor.b = rand(vec3(FragPos.x, FragPos.y, FragPos.z * time * 1.7));

    FragColor = vec4(dynamicColor, 1.0);
}