#include "SpotLight.h"
#include "../include/glm/glm.hpp"
#include "ImGui/imgui.h"

SpotLight::SpotLight(Material* _material, std::string& _name)
    :
    Light(_material, _name),
    m_constant(1.0f),
    m_linear(0.09f),
    m_quadratic(0.032f),
    m_direction(Vector3(0,-1,0)),
    m_cutOff(12.5f),
    m_outerCutOff(17.5f)
{
    m_strength = 1.0f;
}

Vector3 SpotLight::GetLightDirection()
{
    return m_direction;
}

float SpotLight::GetLightCutOff()
{
    return m_cutOff;
}

float SpotLight::GetOuterLightCutOff()
{
    return m_outerCutOff;
}

float SpotLight::GetLightConstant()
{
    return m_constant;
}

float SpotLight::GetLightLinear()
{
    return m_linear;
}

float SpotLight::GetLightQuadratic()
{
    return m_quadratic;
}

void SpotLight::ShowGUIDetails()
{
    if (ImGui::CollapsingHeader("Light Properties"))
    {
        ImGui::Text("Light color");
        ImGui::ColorEdit3("##Light color", &m_color.x);
        ImGui::Spacing();
        ImGui::Text("Light diffuse");
        ImGui::DragFloat3("##Light diffuse", &m_diffuse.x, 0.01f, 0, 1);
        ImGui::Text("Light direction");
        ImGui::DragFloat3("##Light direction", &m_direction.x, 0.01f, -1, 1);
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
        ImGui::Text("Light cutOff");
        ImGui::DragFloat("##Light cutOff", &m_cutOff, 1, 0, 90);
        ImGui::Text("Light outerCutOff");
        ImGui::DragFloat("##Light outerCutOff", &m_outerCutOff, 1, 0, 90);
    }
}
