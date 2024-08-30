#include "PhysicComponent.h"

#include "ImGui/imgui.h"

PhysicComponent::PhysicComponent()
{
    m_active = true;
}

void PhysicComponent::ShowGuiDetails()
{
    if (ImGui::CollapsingHeader("RigidBody"))
    {
        ImGui::Checkbox("Active", &m_active);
        ImGui::Text("Im a physic component");
    }
}
