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
                if(ImGui::MenuItem("Light"))
                {
                    GLUtils::CreateLight();
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
    
    if(ImGui::CollapsingHeader("Light Scene Properties"))
    {
        if(ImGui::TreeNode("Light Intensity"))
        {
            ImGui::DragFloat("##LightIntensity", &m_lightIntensity, 0.01f, 0.0f, 1.0f);
            World::GetInstance()->SetLightIntensity(m_lightIntensity);
            ImGui::TreePop();
        }
    
        if(ImGui::TreeNode("Light Color"))
        {
            Vector3 lightColor = World::GetInstance()->GetLightColor();
            ImGui::ColorEdit3("##LigthColor", &lightColor.x);
            World::GetInstance()->SetLightColor(lightColor);
            ImGui::TreePop();
        }
        
    }
    ImGui::End();
}
