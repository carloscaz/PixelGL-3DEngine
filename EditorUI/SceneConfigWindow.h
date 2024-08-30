#pragma once
#include "GUIWindow.h"

class SceneConfigWindow : public GUIWindow
{
private:
    static SceneConfigWindow* m_instance;
    SceneConfigWindow();

    float m_cameraFov;
    bool m_skyboxActive;
public:
    static SceneConfigWindow* GetInstance();
    void DrawWindow() override;
};
