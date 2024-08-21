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
    sampler2D diffuseMap;
    vec3 diffuse;
    vec3 specular;
    sampler2D specularMap;
    float shininess;
    sampler2D emissionMap;
};
uniform Material material;

struct Light
{
    vec3 position;
    vec3 color;
    vec3 diffuse;
    vec3 specular;
    float strength;
};
uniform Light light;

void main()
{

    vec3 ambient = light.color * light.strength * material.color * vec3(texture(material.diffuseMap, fTex));
    
    vec3 norm = normalize(fNormal);
    vec3 lightDir = normalize(light.position - FragPos); 

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * light.strength  * (diff * vec3(texture(material.diffuseMap, fTex)));

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * light.strength  * (spec * vec3(texture(material.specularMap, fTex))); 

    vec3 emission = vec3(texture(material.emissionMap, fTex));

    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0f);
} 