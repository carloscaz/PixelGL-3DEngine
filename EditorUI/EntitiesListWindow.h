#pragma once
#include "GUIWindow.h"

class ObjectDetailsWindow;

class EntitiesListWindow : public GUIWindow
{
private:
    EntitiesListWindow();
    static EntitiesListWindow* m_instance;
    ObjectDetailsWindow* m_objectWindow;
public:
    static EntitiesListWindow* GetInstance();
    void DrawWindow() override;
    
};
