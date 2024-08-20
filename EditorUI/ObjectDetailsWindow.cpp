#include "ObjectDetailsWindow.h"

#include "ImGui/imgui.h"
#include "../OpenGL/Entities/Entity.h"

ObjectDetailsWindow* ObjectDetailsWindow::m_instance = nullptr;

ObjectDetailsWindow::ObjectDetailsWindow() : m_currentObject(nullptr)
{
}

ObjectDetailsWindow* ObjectDetailsWindow::GetInstance()
{
    if(!m_instance)
    {
        m_instance = new ObjectDetailsWindow();
    }

    return m_instance;
}

void ObjectDetailsWindow::DrawWindow()
{
    if(m_currentObject)
    {
        Vector3 objectPosition = m_currentObject->GetPosition();
        Vector3 objectRotation = m_currentObject->GetRotation();
        Vector3 objectScale = m_currentObject->GetScale();
        
        ImGui::Begin("Object Details");
        ImGui::Text("Position:");
        ImGui::DragFloat3("Position", &objectPosition.x, 0.05f);
        m_currentObject->SetPosition(objectPosition);
        ImGui::Text("Rotation:");
        ImGui::DragFloat3("Rotation", &objectRotation.x, 0.2f, -360.0f, 360.0f);
        m_currentObject->SetRotation(objectRotation);
        ImGui::Text("Scale:");
        ImGui::DragFloat3("Scale", &objectScale.x, 0.2f);
        m_currentObject->SetScale(objectScale);
        ImGui::End();
    }
}

void ObjectDetailsWindow::SetObject(Entity* _entity)
{
    m_currentObject = _entity;
}
