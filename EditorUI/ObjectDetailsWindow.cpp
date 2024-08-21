#include "ObjectDetailsWindow.h"

#include "ImGui/imgui.h"
#include "../OpenGL/Entities/Entity.h"
#include "../OpenGL/Material/Material.h"

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
    ImGui::Begin("Object Details");
    if(m_currentObject)
    {
        Vector3 objectPosition = m_currentObject->GetPosition();
        Vector3 objectRotation = m_currentObject->GetRotation();
        Vector3 objectScale = m_currentObject->GetScale();
        
        if (ImGui::CollapsingHeader("Transform")) {
            if (ImGui::TreeNode("Position")) {
                ImGui::DragFloat3("##Position", &objectPosition.x, 0.05f);
                m_currentObject->SetPosition(objectPosition);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Rotation")) {
                ImGui::DragFloat3("##Rotation", &objectRotation.x, 0.2f, -360.0f, 360.0f);
                m_currentObject->SetRotation(objectRotation);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Scale")) {
                ImGui::DragFloat3("##Scale", &objectScale.x, 0.2f);
                m_currentObject->SetScale(objectScale);
                ImGui::TreePop();
            }
        }
        
        if (ImGui::CollapsingHeader("Object Material")) {
            if(m_currentObject->GetMaterial())
            {
                ImGui::Text("Object Material: %s", m_currentObject->GetMaterial()->GetName().c_str());
            }

            else
            {
                ImGui::Text("Object Material: Material not assigned");
            }
        }
    }
    ImGui::End();
}

void ObjectDetailsWindow::SetObject(Entity* _entity)
{
    m_currentObject = _entity;
}
