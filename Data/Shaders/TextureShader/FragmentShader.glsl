#version 330 core

uniform vec3 color;
uniform sampler2D tex;

in vec2 fTex;

out vec4 FragColor;

void main()
{
    vec3 light = vec3(1.0f) * 0.5f;
    FragColor = texture(tex, fTex) * vec4(light, 1.0f);
} 