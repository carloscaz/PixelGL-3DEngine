#include "DirectionalLight.h"

#include "../../Material/Material.h"
#include "../../Shaders/Shader.h"
#include "ImGui/imgui.h"

DirectionalLight::DirectionalLight(Material* _material)
    :
Light(_material, "Directional Light"),
m_direction(Vector3(-0.2f, -1.0f, -0.3f))
{
    m_strength = 0.5f;
}

void DirectionalLight::Prepare()
{
    Light::Prepare();
}

Vector3 DirectionalLight::GetLightDirection() const
{
    return m_direction;
}

void DirectionalLight::ShowGUIDetails()
{
    if (ImGui::CollapsingHeader("Light Properties"))
    {
        ImGui::Text("Light color");
        ImGui::ColorEdit3("##Light color", &m_color.x);
        ImGui::Spacing();
        ImGui::Text("Light diffuse");
        ImGui::DragFloat3("##Light diffuse", &m_diffuse.x, 0.01f, 0, 1);
        ImGui::Spacing();
        ImGui::Text("Light specular");
        ImGui::DragFloat3("##Light specular", &m_specular.x, 0.01f, 0, 1);
        ImGui::Spacing();
        ImGui::Text("Light strength");
        ImGui::DragFloat("##Light strength", &m_strength, 0.01f, 0, 10);
        ImGui::Text("Light direction");
        ImGui::DragFloat3("##Light direction", &m_direction.x, 0.01f, -1.0f, 1.0f);
    }

}
