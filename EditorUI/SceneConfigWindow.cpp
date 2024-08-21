#include "SceneConfigWindow.h"

#include "../OpenGL/Entities/Camera.h"
#include "../OpenGL/World/World.h"
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
    ImGui::Begin("Scene Config");
    if (ImGui::CollapsingHeader("Fov"))
    {
        ImGui::Text("Camera Fov:");
        ImGui::DragFloat("##CameraFov", &m_cameraFov,0.2f, 0.0f, 100.0f);
        World::GetInstance()->GetActiveCamera()->SetCameraFov(m_cameraFov);
    }
    ImGui::End();
}
