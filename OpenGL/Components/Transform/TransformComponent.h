#pragma once
#include "../Component.h"
#include "../../Math/Vector3/Vector3.h"

class Entity;

class TransformComponent : public Component
{
private:
    //State variable to set the value before start simulate world
    Vector3 m_previousPosition;
    Vector3 m_previousRotation;
    Vector3 m_previousScale;
    
    Vector3 m_position;
    Vector3 m_rotation;
    Vector3 m_scale;

    Entity* m_owner;
public:
    TransformComponent(Entity* _owner);
    TransformComponent(Vector3 _pos, Entity* _owner);
    TransformComponent(Vector3 _pos, Vector3 _rot, Entity* _owner);
    TransformComponent(Vector3 _pos, Vector3 _rot, Vector3 _scale, Entity* _owner);
    ~TransformComponent() override {};
    
    const Vector3& GetPosition() const;
    const Vector3& GetRotation() const;
    const Vector3& GetScale() const;
    Entity* GetOwner() const override;

    void SetPosition(const Vector3& _pos);
    void SetRotation(const Vector3& _rot);
    void SetScale(const Vector3& _scale);
    void SetOwner(Entity* _owner) override;

    void ShowGuiDetails() override;

    void Init() override;
    void Activate() override{};
    void Tick(float _deltaTime) override {};
    void Deactivate() override{};
    void End() override;
};
