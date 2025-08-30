#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;

uniform float time;



void main()
{

    // Animated background
    vec3 bgColor;
    bgColor.r = 0.5 + 0.5 * sin(time);
    bgColor.g = 0.5 + 0.5 * sin(time + 2.0);
    bgColor.b = 0.5 + 0.5 * sin(time + 4.0);
    
    vec3 finalColor = bgColor;
    finalColor += 0.3 * vec3(0.5 + 0.5 * sin(10.0 * TexCoord.x + time), 0.5 + 0.5 * sin(10.0 * TexCoord.y + time), 0.5 + 0.5 * sin(10.0 * (TexCoord.x + TexCoord.y) + time));
    
   
    FragColor = vec4(finalColor, 1.0);
}
