#version 330 core

uniform float ambientLight;
uniform vec3 color;
uniform sampler2D tex;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

in vec2 fTex;
in vec3 fNormal;
in vec3 FragPos; 

out vec4 FragColor;

struct Material
{
    vec3 color;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

void main()
{

    vec3 ambient = lightColor * ambientLight * material.color;
    
    vec3 norm = normalize(fNormal);
    vec3 lightDir = normalize(lightPos - FragPos); 

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * (diff * material.diffuse);

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * (spec * material.specular); 

    vec3 result = (ambient + diffuse + specular);
    FragColor = texture(tex, fTex) * vec4(result, 1.0f);
} 