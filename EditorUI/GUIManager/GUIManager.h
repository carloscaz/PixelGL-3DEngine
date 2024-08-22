#pragma once
#include "../../Dependencies/include/GLFW/glfw3.h"

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

    GLFWwindow* m_glfwWindow;
public:
    static GUIManager* GetInstance();

    ObjectDetailsWindow* GetObjectWindow();
    void CreateDockingSpace();
    void SetGLFWWindow(GLFWwindow* _window);
    GLFWwindow* GetGlFWwindow() const;

    void Tick();
    void Draw();
};
