#include "GUIManager.h"

#include "../EntitiesListWindow.h"
#include "../ObjectDetailsWindow.h"
#include "../SceneConfigWindow.h"

GUIManager* GUIManager::m_instance = nullptr;

GUIManager::GUIManager()
{
    m_entitiesWindow = EntitiesListWindow::GetInstance();
    m_objectDetailsWindow = ObjectDetailsWindow::GetInstance();
    m_sceneConfigWindow = SceneConfigWindow::GetInstance();
}

GUIManager* GUIManager::GetInstance()
{
    if(!m_instance)
    {
        m_instance = new GUIManager();
    }

    return m_instance;
}

ObjectDetailsWindow* GUIManager::GetObjectWindow()
{
    return m_objectDetailsWindow;
}

void GUIManager::Draw()
{
    m_entitiesWindow->DrawWindow();
    m_objectDetailsWindow->DrawWindow();
    m_sceneConfigWindow->DrawWindow();
}
