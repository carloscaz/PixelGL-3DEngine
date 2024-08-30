#include "PointLight.h"

#include <iostream>
#include <ostream>

#include "../../Material/Material.h"
#include "../../Mesh/Mesh.h"
#include "../../Shaders/Shader.h"
#include "ImGui/imgui.h"

PointLight::PointLight(Material* _material, std::string& _name)
    :
    Light(_material, _name),
    m_constant(1.0f),
    m_linear(0.09f),
    m_quadratic(0.032f)
{}

PointLight::PointLight(std::string& _name, Mesh* _mesh)
:
    Light(nullptr, _name),
    m_constant(1.0f),
    m_linear(0.09f),
    m_quadratic(0.032f)
{
    m_meshes.push_back(_mesh);
}

float PointLight::GetLightConstant()
{
    return m_constant;
}

float PointLight::GetLightLinear()
{
    return m_linear;
}

float PointLight::GetLightQuadratic()
{
    return m_quadratic;
}

void PointLight::Prepare()
{
    //Light::Prepare();
    for (Mesh* mesh : m_meshes)
    {
        mesh->GetMaterial()->GetShader()->SetVec3("color", m_diffuse);
    }
}

void PointLight::ShowGUIDetails()
{
    Light::ShowGUIDetails();
    
    if (ImGui::CollapsingHeader("Light Properties"))
    {
        ImGui::Text("Light color");
        ImGui::ColorEdit3("##Light color", &m_color.x);
        ImGui::Spacing();
        ImGui::Text("Light diffuse");
        ImGui::ColorEdit3("##Light diffuse", &m_diffuse.x);
        ImGui::Spacing();
        ImGui::Text("Light specular");
        ImGui::DragFloat3("##Light specular", &m_specular.x, 0.01f, 0, 1);
        ImGui::Spacing();
        ImGui::Text("Light strength");
        ImGui::DragFloat("##Light strength", &m_strength, 0.01f, 0, 10);
        ImGui::Text("Light constant");
        ImGui::DragFloat("##Light constant", &m_constant, 0.1f, 0, 1);
        ImGui::Text("Light linear");
        ImGui::DragFloat("##Light linear", &m_linear, 0.1f, 0, 1);
        ImGui::Text("Light quadratic");
        ImGui::DragFloat("##Light quadratic", &m_quadratic, 0.1f, 0, 1);
    }
}
