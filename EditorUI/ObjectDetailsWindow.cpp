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

//Draw object details ImGui window
void ObjectDetailsWindow::DrawWindow()
{
    ImGui::Begin("Object Details");
    if(m_currentObject)
    {
        m_currentObject->ShowGUIDetails();
    }
    ImGui::End();
}

void ObjectDetailsWindow::SetObject(Entity* _entity)
{
    m_currentObject = _entity;
}
