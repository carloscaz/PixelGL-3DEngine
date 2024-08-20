#pragma once
#include "../Textures/Texture.h"
#include "../include/glm/glm.hpp"

class Shader;

class Material
{
private:
    Texture* m_texture;
    Shader* m_shader;
public:
    Material(Texture* _texture, Shader* _shader);
    void Prepare();

    Shader* GetShader() const;
};
