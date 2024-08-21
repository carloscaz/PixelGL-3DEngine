#pragma once

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
public:
    static GUIManager* GetInstance();

    ObjectDetailsWindow* GetObjectWindow();

    void Draw();
};
