#include "GUIManager.h"

#include <cstdio>

#include "../EntitiesListWindow.h"
#include "../ObjectDetailsWindow.h"
#include "../SceneConfigWindow.h"

#include "ImGui/imgui.h"

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

void GUIManager::CreateDockingSpace()
{
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
      ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
      ImGuiWindowFlags_NoBackground;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("InvisibleWindow", nullptr, windowFlags);
    ImGui::PopStyleVar(3);

    ImGuiID dockSpaceId = ImGui::GetID("InvisibleWindowDockSpace");

    ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
    ImGui::End();
}

void GUIManager::SetGLFWWindow(GLFWwindow* _window)
{
    m_glfwWindow = _window;
}

GLFWwindow* GUIManager::GetGlFWwindow() const
{
    return m_glfwWindow;
}

void GUIManager::Tick()
{
}

void GUIManager::Draw()
{
    m_entitiesWindow->DrawWindow();
    m_objectDetailsWindow->DrawWindow();
    m_sceneConfigWindow->DrawWindow();
}
