#include "SceneConfigWindow.h"

#include "LogsWindow.h"
#include "../OpenGL/GlUtils.h"
#include "../OpenGL/Entities/Camera.h"
#include "../OpenGL/World/World.h"
#include "GUIManager/GUIManager.h"
#include "ImGui/imgui.h"

SceneConfigWindow* SceneConfigWindow::m_instance = nullptr;

SceneConfigWindow::SceneConfigWindow() :
m_cameraFov(45.0f),
m_skyboxActive(true)
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
            if(ImGui::BeginMenu("Create new entity"))
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
                        LogsWindow::GetInstance()->AddLog("New Directional Light Created");
                    }
                    if(ImGui::MenuItem("PointLight"))
                    {
                        GLUtils::CreatePointLight();
                        LogsWindow::GetInstance()->AddLog("New Point Light Created");
                    }
                    if(ImGui::MenuItem("SpotLight"))
                    {
                        GLUtils::CreateSpotLight();
                        LogsWindow::GetInstance()->AddLog("New Spotlight Created");
                    }
                    ImGui::EndMenu();
                }
                if(ImGui::MenuItem("Mesh"))
                {
                    GLUtils::CreateDemoMesh();
                    LogsWindow::GetInstance()->AddLog("Mesh Created");
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

    ImGui::Separator();
    if(ImGui::Checkbox("Skybox Active", &m_skyboxActive))
    {
        World::GetInstance()->SetSkybox(m_skyboxActive);
        if(m_skyboxActive)
        {
            LogsWindow::GetInstance()->AddLog("Skybox enabled");
        }

        else
        {
            LogsWindow::GetInstance()->AddLog("Skybox disabled");
        }
        
    }
    ImGui::End();
}
