#include "Material.h"
#include "glad/glad.h"
#include <GL/gl.h>

#include "../Shaders/Shader.h"

Material::Material(Texture* _texture, Shader* _shader) : m_texture(_texture), m_shader(_shader), m_name("Default Material")
{
}

Material::Material(Texture* _texture, Shader* _shader, std::string& _name) : m_texture(_texture), m_shader(_shader), m_name(_name)
{
}

void Material::Prepare()
{
    m_shader->UseShader();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->GetId());
}

Shader* Material::GetShader() const
{
    return m_shader;
}

std::string& Material::GetName()
{
    return m_name;
}
