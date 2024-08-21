#version 330 core

uniform vec3 color;
uniform sampler2D tex;

in vec2 fTex;

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f);
} 