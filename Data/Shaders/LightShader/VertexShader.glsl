#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTex;
layout (location = 2) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 fTex;
out vec3 fNormal;
out vec3 FragPos; 

void main()
{
    fTex = vTex;
    fNormal = mat3(transpose(inverse(model))) * vNormal;
    gl_Position =  projection * view * model * vec4(vPos, 1.0);
    FragPos = vec3(model * vec4(vPos, 1.0));
}