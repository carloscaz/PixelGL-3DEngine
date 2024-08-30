#pragma once

class Component
{
protected:
    bool m_active;
public:
    Component() {};
    
    virtual void ShowGuiDetails() = 0;

    virtual void Activate() = 0;
    virtual void Tick() = 0;
    virtual void Deactivate() = 0;
};
