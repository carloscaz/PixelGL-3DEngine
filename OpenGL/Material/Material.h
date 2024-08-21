#pragma once
#include <string>

#include "../Textures/Texture.h"
#include "../include/glm/glm.hpp"

class Shader;

class Material
{
private:
    Texture* m_texture;
    Shader* m_shader;

    std::string m_name;
public:
    Material(Texture* _texture, Shader* _shader);
    Material(Texture* _texture, Shader* _shader, std::string& _name);
    void Prepare();

    Shader* GetShader() const;

    std::string& GetName();
};
