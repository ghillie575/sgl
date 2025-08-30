#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform float time;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

void main()
{
    // Dynamic color based on position and time
    vec3 dynamicColor;
    dynamicColor.r = 0.5 + 0.5 * sin(time + FragPos.x);
    dynamicColor.g = 0.5 + 0.5 * sin(time + FragPos.y);
    dynamicColor.b = 0.5 + 0.5 * sin(time + FragPos.z);

    // Modulate material colors with dynamic color
    
    FragColor = vec4(dynamicColor, 1.0);
}