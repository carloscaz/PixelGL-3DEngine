#include "Material.h"
#include "glad/glad.h"
#include <GL/gl.h>

#include "../Entities/Camera.h"
#include "../Entities/Lights/DirectionalLight.h"
#include "../Entities/Lights/PointLight.h"
#include "../Entities/Lights/SpotLight.h"
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

Material::Material(Shader* _shader, std::string& _name, const Vector3& _color,
                   const Vector3& _diffuse, const Vector3& _specular, float _shininess)
    : m_shader(_shader),
      m_name(_name),
      m_color(_color),
      m_diffuse(_diffuse),
      m_specular(_specular),
      m_shininess(_shininess)
{}

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

    if(World::GetInstance()->GetDirectionaLight())
    {
        World::GetInstance()->GetDirectionaLight()->Prepare();
        m_shader->SetVec3("dirLight.direction", World::GetInstance()->GetDirectionaLight()->GetLightDirection());
        m_shader->SetVec3("dirLight.color", World::GetInstance()->GetDirectionaLight()->GetLightColor());
        m_shader->SetVec3("dirLight.diffuse", World::GetInstance()->GetDirectionaLight()->GetLightDiffuse());
        m_shader->SetVec3("dirLight.specular", World::GetInstance()->GetDirectionaLight()->GetLightSpecular());
        m_shader->SetFloat("dirLight.strength", World::GetInstance()->GetDirectionaLight()->GetLightStrength());
    }
    
    // for (PointLight* light : World::GetInstance()->GetPointLights())
    // {
    //     light->Prepare();
    // }

    // for(SpotLight* light : World::GetInstance()->GetSpotLights())
    // {
    //     light->Prepare();
    // }
    
    //Set lights
    m_shader->SetInt("numPointLights", World::GetInstance()->GetPointLights().size());
    m_shader->SetInt("numSpotLights", World::GetInstance()->GetSpotLights().size());

    unsigned int pointLightIndex = 0;
    for(PointLight* light : World::GetInstance()->GetPointLights())
    {
        m_shader->SetVec3((std::string("pointLights[") + std::to_string(pointLightIndex) + std::string("].position")).c_str(), light->GetPosition());
        m_shader->SetVec3((std::string("pointLights[") + std::to_string(pointLightIndex) + std::string("].color")).c_str(), light->GetLightColor());
        m_shader->SetVec3((std::string("pointLights[") + std::to_string(pointLightIndex) + std::string("].diffuse")).c_str(), light->GetLightDiffuse());
        m_shader->SetVec3((std::string("pointLights[") + std::to_string(pointLightIndex) + std::string("].specular")).c_str(), light->GetLightSpecular());
        m_shader->SetFloat((std::string("pointLights[") + std::to_string(pointLightIndex) + std::string("].strength")).c_str(), light->GetLightStrength());
        m_shader->SetFloat((std::string("pointLights[") + std::to_string(pointLightIndex) + std::string("].constant")).c_str(), light->GetLightConstant());
        m_shader->SetFloat((std::string("pointLights[") + std::to_string(pointLightIndex) + std::string("].linear")).c_str(), light->GetLightLinear());
        m_shader->SetFloat((std::string("pointLights[") + std::to_string(pointLightIndex) + std::string("].quadratic")).c_str(), light->GetLightQuadratic());
        ++pointLightIndex;
    }

    unsigned int spotLightIndex = 0;
    for(SpotLight* light : World::GetInstance()->GetSpotLights())
    {
        m_shader->SetVec3((std::string("spotLights[") + std::to_string(spotLightIndex) + std::string("].position")).c_str(), light->GetPosition());
        m_shader->SetVec3((std::string("spotLights[") + std::to_string(spotLightIndex) + std::string("].color")).c_str(), light->GetLightColor());
        m_shader->SetVec3((std::string("spotLights[") + std::to_string(spotLightIndex) + std::string("].diffuse")).c_str(), light->GetLightDiffuse());
        m_shader->SetVec3((std::string("spotLights[") + std::to_string(spotLightIndex) + std::string("].specular")).c_str(), light->GetLightSpecular());
        m_shader->SetFloat((std::string("spotLights[") + std::to_string(spotLightIndex) + std::string("].strength")).c_str(), light->GetLightStrength());
        m_shader->SetFloat((std::string("spotLights[") + std::to_string(spotLightIndex) + std::string("].constant")).c_str(), light->GetLightConstant());
        m_shader->SetFloat((std::string("spotLights[") + std::to_string(spotLightIndex) + std::string("].linear")).c_str(), light->GetLightLinear());
        m_shader->SetFloat((std::string("spotLights[") + std::to_string(spotLightIndex) + std::string("].quadratic")).c_str(), light->GetLightQuadratic());
        m_shader->SetVec3((std::string("spotLights[") + std::to_string(spotLightIndex) + std::string("].direction")).c_str(), light->GetLightDirection());
        m_shader->SetFloat((std::string("spotLights[") + std::to_string(spotLightIndex) + std::string("].cutOff")).c_str(), glm::cos(glm::radians(light->GetLightCutOff())));
        m_shader->SetFloat((std::string("spotLights[") + std::to_string(spotLightIndex) + std::string("].outerCutOff")).c_str(), glm::cos(glm::radians(light->GetOuterLightCutOff())));
        ++spotLightIndex;
    }
    
    
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

void Material::ShowGUIDetails(int _id)
{
    if (ImGui::CollapsingHeader((std::string("Object Material##") + std::to_string(_id)).c_str()))
    {
        ImGui::Text("Object Material: %s", m_name.c_str());

        if (ImGui::TreeNode((std::string("Material Textures##") + std::to_string(_id)).c_str()))
        {
            for (Texture* texture : m_textures)
            {
                ImGui::Text(texture->GetName());
                ImGui::Image((void*)(intptr_t)texture->GetId(), ImVec2(50, 50));
            }
            ImGui::TreePop();
        }
        
        ImGui::Spacing();
        if(ImGui::TreeNode((std::string("Material Properties##") + std::to_string(_id)).c_str()))
        {
            ImGui::Text("Material diffuse");
            ImGui::DragFloat3("##Material diffuse", &m_diffuse.x, 0.01f, 0, 1);
            ImGui::Spacing();
            ImGui::Text("Material specular");
            ImGui::DragFloat3("##Material specular", &m_specular.x, 0.01f, 0, 1);
            ImGui::Spacing();
            ImGui::Text("Material shininess");
            ImGui::DragFloat("##Material shininess", &m_shininess, 1, 1, 100);
            ImGui::TreePop();
        }
     
    }
}

void Material::AddTexture(Texture* _texture)
{
    m_textures.push_back(_texture);
}
