#pragma once
#include "GUIWindow.h"
class Entity;

class ObjectDetailsWindow : public GUIWindow
{
private:
    Entity* m_currentObject;
    static ObjectDetailsWindow* m_instance;
    ObjectDetailsWindow();
    
public:
    static ObjectDetailsWindow* GetInstance();
    void DrawWindow() override;

    void SetObject(Entity* _entity);
};
