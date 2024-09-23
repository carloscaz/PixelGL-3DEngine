#include "SceneConfigWindow.h"

#include "Log.h"
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

//Draw config scene ImGui window
void SceneConfigWindow::DrawWindow()
{
    ImGui::Begin("Scene Config",nullptr, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            //Menu to create new entities in the engine
            if(ImGui::BeginMenu("Create new entity"))
            {
                ImGui::SeparatorText("Entities list");
                //Create a cube
                if(ImGui::MenuItem("Cube"))
                {
                    GLUtils::CreateCube();
                }
                //Create lights menu
                if(ImGui::BeginMenu("Lights"))
                {
                    if(ImGui::MenuItem("Directional Light"))
                    {
                        GLUtils::CreateDirectionalLight();
                        std::string message = std::string("New Directional Light Created");
                        LogsWindow::GetInstance()->AddLog(new Log(message, logCategory::eInfoLog));
                    }
                    if(ImGui::MenuItem("PointLight"))
                    {
                        GLUtils::CreatePointLight();
                        std::string message = std::string("New Point Light Created");
                        LogsWindow::GetInstance()->AddLog(new Log(message, logCategory::eInfoLog));
                    }
                    if(ImGui::MenuItem("SpotLight"))
                    {
                        GLUtils::CreateSpotLight();
                        std::string message = std::string("New Spotlight Created");
                        LogsWindow::GetInstance()->AddLog(new Log(message, logCategory::eInfoLog));
                    }
                    ImGui::EndMenu();
                }

                //Create mesh
                if(ImGui::MenuItem("Mesh"))
                {
                    GLUtils::CreateDemoMesh();
                    std::string message = std::string("Mesh Created");
                    LogsWindow::GetInstance()->AddLog(new Log(message, logCategory::eInfoLog));
                }
                ImGui::EndMenu();
            }

            //End engine
            if(ImGui::MenuItem("Close engine"))
            {
                glfwSetWindowShouldClose(GUIManager::GetInstance()->GetGlFWwindow(), true);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    //Camera fov modifier
    if (ImGui::CollapsingHeader("Camera Fov"))
    {
        ImGui::Text("Camera Fov:");
        ImGui::DragFloat("##CameraFov", &m_cameraFov,0.2f, 0.0f, 100.0f);
        World::GetInstance()->GetActiveCamera()->SetCameraFov(m_cameraFov);
    }

    //Enable/Disable skybox
    ImGui::Separator();
    if(ImGui::Checkbox("Skybox Active", &m_skyboxActive))
    {
        World::GetInstance()->SetSkybox(m_skyboxActive);
        if(m_skyboxActive)
        {
            std::string message = std::string("Skybox enabled");
            LogsWindow::GetInstance()->AddLog(new Log(message, logCategory::eInfoLog));
        }
        else
        {
            std::string message = std::string("Skybox disabled");
            LogsWindow::GetInstance()->AddLog(new Log(message, logCategory::eInfoLog));
        }
    }
    ImGui::End();
}
