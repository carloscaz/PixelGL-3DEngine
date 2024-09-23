#include "TransformComponent.h"

#include "../../EditorUI/LogsWindow.h"
#include "../../Entities/Entity.h"
#include "ImGui/imgui.h"

TransformComponent::TransformComponent(Entity* _owner) :
    m_position(Vector3(0,0,0)),
    m_rotation(Vector3(0,0,0)),
    m_scale(Vector3(0,0,0)),
    m_owner(_owner)
{
    m_active = true;
}

TransformComponent::TransformComponent(Vector3 _pos, Entity* _owner) :
    m_position(Vector3(_pos)),
    m_rotation(Vector3(0,0,0)),
    m_scale(Vector3(0,0,0)),
    m_owner(_owner)
{
    m_active = true;
}

TransformComponent::TransformComponent(Vector3 _pos, Vector3 _rot, Entity* _owner) :
    m_position(_pos),
    m_rotation(_rot),
    m_scale(Vector3(0,0,0)),
    m_owner(_owner)
{
    m_active = true;
}

TransformComponent::TransformComponent(Vector3 _pos, Vector3 _rot, Vector3 _scale, Entity* _owner) :
    m_position(_pos),
    m_rotation(_rot),
    m_scale(_scale),
    m_owner(_owner)
{
    m_active = true;
}

const Vector3& TransformComponent::GetPosition() const
{
    return m_position;
}

const Vector3& TransformComponent::GetRotation() const
{
    return m_rotation;
}

const Vector3& TransformComponent::GetScale() const
{
    return m_scale;
}

Entity* TransformComponent::GetOwner() const
{
    return m_owner;
}

void TransformComponent::SetOwner(Entity* _owner)
{
    m_owner = _owner;
}

void TransformComponent::SetPosition(const Vector3& _pos)
{
    m_position = _pos;
}

void TransformComponent::SetRotation(const Vector3& _rot)
{
    m_rotation = _rot;
}

void TransformComponent::SetScale(const Vector3& _scale)
{
    m_scale = _scale;
}

//Transform component ImGui window
void TransformComponent::ShowGuiDetails()
{
    if (ImGui::CollapsingHeader("Transform Component"))
    {
        //Position, Rotation & Scale of the entity
        ImGui::Text("Position");
        ImGui::DragFloat3("##TransformPosition", &m_position.x, 0.05f);
        
        ImGui::Text("Rotation");
        ImGui::DragFloat3("##TransformRotation", &m_rotation.x, 0.2f);
        m_owner->SetRotation(m_rotation);

        ImGui::Text("Scale");
        ImGui::DragFloat3("##TransformScale", &m_scale.x, 0.05f);
        m_owner->SetScale(m_scale);
        ImGui::Separator();
    }
}

//Save the data of the component before simulation
void TransformComponent::Init()
{
    m_previousPosition = m_position;
    m_previousRotation = m_rotation;
    m_previousScale = m_scale;
}

//Reset the data of the component after simulation
void TransformComponent::End()
{
    m_position = m_previousPosition;
    m_rotation = m_previousRotation;
    m_scale = m_previousScale;
}
