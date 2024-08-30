#version 330 core
out vec4 FragColor;

in vec3 TexCoords;
uniform float lightStrength;
uniform vec3 lightColor;
uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, TexCoords) * lightStrength * vec4(lightColor, 1.0f);
}