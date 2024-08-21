#include "Material.h"
#include "glad/glad.h"
#include <GL/gl.h>

#include "../Entities/Camera.h"
#include "../Entities/Light.h"
#include "../Shaders/Shader.h"
#include "../World/World.h"
#include "ImGui/imgui.h"

Material::Material(Texture* _texture, Shader* _shader) : m_shader(_shader), m_name("Default Material")
{
    m_textures.push_back(_texture);
}

Material::Material(Texture* _texture, Shader* _shader, std::string& _name) : m_shader(_shader), m_name(_name)
{
    m_textures.push_back(_texture);
}

Material::Material(Texture* _texture, Shader* _shader, std::string& _name, const Vector3& _color,
                   const Vector3& _diffuse, const Vector3& _specular, float _shininess)
    : m_shader(_shader),
      m_name(_name),
      m_color(_color),
      m_diffuse(_diffuse),
      m_specular(_specular),
      m_shininess(_shininess)
{
    m_textures.push_back(_texture);
}

void Material::Prepare()
{
    m_shader->UseShader();
    m_shader->SetInt("material.diffuseMap", 0);
    m_shader->SetInt("material.specularMap", 1);
    m_shader->SetInt("material.emissionMap", 2);
    for (int i = 0; i < m_textures.size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, m_textures[i]->GetId());
    }

    World::GetInstance()->GetLight(0)->Prepare();

    //Set lights
    m_shader->SetFloat("ambientLight", World::GetInstance()->GetlightIntensity());
    m_shader->SetVec3("light.position", World::GetInstance()->GetLight(0)->GetPosition());
    m_shader->SetVec3("light.color", World::GetInstance()->GetLight(0)->GetLightColor());
    m_shader->SetVec3("light.diffuse", World::GetInstance()->GetLight(0)->GetLightDiffuse());
    m_shader->SetVec3("light.specular", World::GetInstance()->GetLight(0)->GetLightSpecular());
    m_shader->SetFloat("light.strength", World::GetInstance()->GetLight(0)->GetLightStrength());
    m_shader->SetVec3("viewPos", World::GetInstance()->GetActiveCamera()->GetPosition());

    m_shader->SetVec3("material.color", m_color);
    m_shader->SetVec3("material.diffuse", m_diffuse);
    m_shader->SetVec3("material.specular", m_specular);
    m_shader->SetFloat("material.shininess", m_shininess);
}

Shader* Material::GetShader() const
{
    return m_shader;
}

std::string& Material::GetName()
{
    return m_name;
}

void Material::ShowGUIDetails()
{
    if (ImGui::CollapsingHeader("Object Material"))
    {
        ImGui::Text("Object Material: %s", m_name.c_str());

        if (ImGui::TreeNode("Material Textures"))
        {
            for (Texture* texture : m_textures)
            {
                ImGui::Text(texture->GetName());
                ImGui::Image((void*)(intptr_t)texture->GetId(), ImVec2(50, 50));
            }
            ImGui::TreePop();
        }
        
        ImGui::Spacing();
        if(ImGui::TreeNode("Material Properties"))
        {
            ImGui::Text("Material color");
            ImGui::ColorEdit3("##Material color", &m_color.x);
            ImGui::Spacing();
            ImGui::Text("Material diffuse");
            ImGui::DragFloat3("##Material diffuse", &m_diffuse.x, 0.01f, 0, 1);
            ImGui::Spacing();
            ImGui::Text("Material specular");
            ImGui::DragFloat3("##Material specular", &m_specular.x, 0.01f, 0, 1);
            ImGui::Spacing();
            ImGui::Text("Material shininess");
            ImGui::DragFloat("##Material shininess", &m_shininess, 1, 0, 100);
            ImGui::TreePop();
        }
     
    }
}

void Material::AddTexture(Texture* _texture)
{
    m_textures.push_back(_texture);
}
