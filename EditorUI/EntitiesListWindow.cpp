#include "EntitiesListWindow.h"

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
        bool isSelected = (entity == m_selectedEntity);
        if (ImGui::Selectable(entity->GetName().c_str(), isSelected))
        {
            m_selectedEntity = entity;
            GUIManager::GetInstance()->GetObjectWindow()->SetObject(entity);
        }
    }
    ImGui::End();
}
