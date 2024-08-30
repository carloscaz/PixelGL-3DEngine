#include "EntitiesListWindow.h"

#include <iostream>

#include "ImGui/imgui.h"
#include "../OpenGL/Entities/Entity.h"
#include "../OpenGL/World/World.h"
#include "ObjectDetailsWindow.h"
#include "GUIManager/GUIManager.h"

static Entity* m_selectedEntity;
EntitiesListWindow* EntitiesListWindow::m_instance = nullptr;

EntitiesListWindow::EntitiesListWindow()
{
    m_objectWindow = ObjectDetailsWindow::GetInstance();
}

EntitiesListWindow* EntitiesListWindow::GetInstance()
{
    if(!m_instance)
    {
        m_instance = new EntitiesListWindow();
    }

    return m_instance;
}

void EntitiesListWindow::DrawWindow()
{
    ImGui::Begin("Entities List");
    
    for (Entity* entity : World::GetInstance()->GetEntities())
    {
        if(entity->GetIsSelectable())
        {
            bool isSelected = (entity == m_selectedEntity);
            if (ImGui::Selectable(entity->GetName().c_str(), isSelected))
            {
                m_selectedEntity = entity;
            }
            if(ImGui::IsItemClicked(ImGuiMouseButton_Left)) //Check if ImGui is pressed with left mouse
            {
                GUIManager::GetInstance()->GetObjectWindow()->SetObject(entity);
            }

            if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) //Check if ImGui is pressed with right mouse
            {
                ImGui::OpenPopup("Object Options Menu");
            }
        
            if (ImGui::BeginPopup("Object Options Menu"))
            {
                if (ImGui::MenuItem("Delete Entity"))
                {
                
                }

                ImGui::EndPopup();
            }
        }
    }
        
    ImGui::End();
}
