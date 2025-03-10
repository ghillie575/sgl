#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos; 
uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float ambientStrength;
uniform vec3 camPos;
void main()
{
    vec3 ambient = ambientStrength * lightColor;
  	
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
            
    float specularStrength = 0.5;
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = specularStrength * spec * lightColor;  

     vec3 result = (ambient + diffuse + specular) * vertexColor.rgb;
     FragColor = texture(texture1, TexCoord) * vec4(result, 1.0);
}