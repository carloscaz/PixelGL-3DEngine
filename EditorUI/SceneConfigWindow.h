#pragma once
#include "GUIWindow.h"

class SceneConfigWindow : public GUIWindow
{
private:
    static SceneConfigWindow* m_instance;
    SceneConfigWindow();

    float m_cameraFov = 45.0f;
    float m_lightIntensity = 1.0f;
public:
    static SceneConfigWindow* GetInstance();
    void DrawWindow() override;
};
