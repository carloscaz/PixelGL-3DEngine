#include "Light.h"

#include "../../Material/Material.h"
#include "../../Shaders/Shader.h"
#include "ImGui/imgui.h"

Light::Light(Material* _material, const std::string& _name)
    :
    Entity(_material, _name),
    m_color(Vector3( 1.0f, 1.0f, 1.0f)),
    m_diffuse(Vector3(1.0f, 1.0f, 1.0f)),
    m_specular(Vector3(1.0f, 1.0f, 1.0f)),
    m_strength(0.1f)
{
    m_scale = Vector3(0.2f, 0.2f, 0.2f);
    m_isSelectable = true;
}

Light::~Light()
{
    
}

void Light::ShowGUIDetails()
{
    for(Component* component : m_components)
    {
        component->ShowGuiDetails();
    }
    
    // if (ImGui::CollapsingHeader("Light Properties"))
    // {
    //     ImGui::Text("Light color");
    //     ImGui::ColorEdit3("##Light color", &m_color.x);
    //     ImGui::Spacing();
    //     ImGui::Text("Light diffuse");
    //     ImGui::DragFloat3("##Light diffuse", &m_diffuse.x, 0.01f, 0, 1);
    //     ImGui::Spacing();
    //     ImGui::Text("Light specular");
    //     ImGui::DragFloat3("##Light specular", &m_specular.x, 0.01f, 0, 1);
    //     ImGui::Spacing();
    //     ImGui::Text("Light strength");
    //     ImGui::DragFloat("##Light strength", &m_strength, 0.01f, 0, 10);
    // }
}

Vector3 Light::GetLightColor() const
{
    return m_color;
}

Vector3 Light::GetLightDiffuse() const
{
    return m_diffuse;
}

Vector3 Light::GetLightSpecular() const
{
    return m_specular;
}

float Light::GetLightStrength() const
{
    return m_strength;
}

void Light::Prepare()
{
    
}
