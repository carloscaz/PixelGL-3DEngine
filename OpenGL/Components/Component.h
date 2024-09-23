#pragma once

class Entity;

class Component
{
protected:
    bool m_active = true;
    Entity* m_owner = nullptr;
public:
    Component() {};
    virtual ~Component() {};
    virtual Entity* GetOwner() const;
    virtual void SetOwner(Entity* _owner);
    
    virtual void ShowGuiDetails() = 0;

    virtual void Activate() = 0;
    virtual void Init() = 0;
    virtual void Tick(float _deltaTime) = 0;
    virtual void Deactivate() = 0;
    virtual void End() = 0;
};
