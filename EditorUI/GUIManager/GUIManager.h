#pragma once
#include <vector>

#include "GLFW/glfw3.h"

class GUIWindow;
class SceneConfigWindow;
class ObjectDetailsWindow;
class EntitiesListWindow;


class GUIManager
{
    GUIManager();
    static GUIManager* m_instance;
    EntitiesListWindow* m_entitiesWindow;
    ObjectDetailsWindow* m_objectDetailsWindow;
    SceneConfigWindow* m_sceneConfigWindow;

    std::vector<GUIWindow*> m_windows;

    GLFWwindow* m_glfwWindow;
public:
    static GUIManager* GetInstance();

    ObjectDetailsWindow* GetObjectWindow();
    void CreateDockingSpace();
    void SetGLFWWindow(GLFWwindow* _window);
    GLFWwindow* GetGlFWwindow() const;

    void AddWindow(GUIWindow* _window);

    void Tick();
    void Draw();
};
