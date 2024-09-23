#pragma once
#include "GUIWindow.h"

class ObjectDetailsWindow;

//ImGui window for a list of the entitities in the world
class EntitiesListWindow : public GUIWindow
{
private:
    EntitiesListWindow(); //Window constructor private. Creation method in singleton
    static EntitiesListWindow* m_instance;
    ObjectDetailsWindow* m_objectWindow;
public:
    ~EntitiesListWindow() override;
    static EntitiesListWindow* GetInstance();
    void DrawWindow() override; //Draw EntitiesList window
    
};
