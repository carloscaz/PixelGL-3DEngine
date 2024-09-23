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

struct DirLight
{
    vec3 direction;
    vec3 color;
    vec3 diffuse;
    vec3 specular;
    float strength;
};
uniform DirLight dirLight;
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = vec3(light.strength) * vec3(texture(material.diffuseMap, fTex));
    vec3 diffuse  = light.diffuse * light.strength * diff * vec3(texture(material.diffuseMap, fTex));
    vec3 specular = light.specular * light.strength * spec * vec3(texture(material.specularMap, fTex));
    return (ambient + diffuse + specular);
}


struct PointLight 
{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float strength;
};
uniform PointLight pointLights[4];
uniform int numPointLights;
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = vec3(light.strength) * vec3(texture(material.diffuseMap, fTex));
    vec3 diffuse  = light.diffuse * (diff * vec3(texture(material.diffuseMap, fTex)));
    vec3 specular = light.specular * (spec * vec3(texture(material.specularMap, fTex)));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

struct SpotLight
{
    vec3 position;  
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 color;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
    float strength;
};
uniform SpotLight spotLights[4];
uniform int numSpotLights;
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = vec3(0.0f) * vec3(texture(material.diffuseMap, fTex));
    vec3 diffuse  = light.diffuse * (diff * vec3(texture(material.diffuseMap, fTex)));
    vec3 specular = light.specular * (spec * vec3(texture(material.specularMap, fTex)));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

void main()
{
    vec3 norm = normalize(fNormal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    for(int i = 0; i < numPointLights; ++i)
    {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }

    for(int i = 0; i < numSpotLights; ++i)
    {
        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
    }

    
    FragColor = vec4(result, 1.0f);
} 