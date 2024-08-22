#include "SceneConfigWindow.h"

#include "../OpenGL/GlUtils.h"
#include "../OpenGL/Entities/Camera.h"
#include "../OpenGL/World/World.h"
#include "GUIManager/GUIManager.h"
#include "ImGui/imgui.h"

SceneConfigWindow* SceneConfigWindow::m_instance = nullptr;

SceneConfigWindow::SceneConfigWindow()
{
}

SceneConfigWindow* SceneConfigWindow::GetInstance()
{
    if(!m_instance)
    {
        m_instance = new SceneConfigWindow();
    }
    return m_instance;
}

void SceneConfigWindow::DrawWindow()
{
    
    ImGui::Begin("Scene Config",nullptr, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            if(ImGui::BeginMenu("New entity"))
            {
                ImGui::SeparatorText("Entities list");
                if(ImGui::MenuItem("Cube"))
                {
                    GLUtils::CreateCube();
                }
                if(ImGui::BeginMenu("Lights"))
                {
                    if(ImGui::MenuItem("Directional Light"))
                    {
                        GLUtils::CreateDirectionalLight();
                    }
                    if(ImGui::MenuItem("PointLight"))
                    {
                        GLUtils::CreatePointLight();
                    }
                    if(ImGui::MenuItem("SpotLight"))
                    {
                        GLUtils::CreateSpotLight();
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            if(ImGui::MenuItem("Close engine"))
            {
                glfwSetWindowShouldClose(GUIManager::GetInstance()->GetGlFWwindow(), true);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    if (ImGui::CollapsingHeader("Camera Fov"))
    {
        ImGui::Text("Camera Fov:");
        ImGui::DragFloat("##CameraFov", &m_cameraFov,0.2f, 0.0f, 100.0f);
        World::GetInstance()->GetActiveCamera()->SetCameraFov(m_cameraFov);
    }
    ImGui::End();
}
