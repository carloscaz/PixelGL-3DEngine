#pragma once
#include "Component.h"
#include "../../Math/Vector3/Vector3.h"
#include "GLFW/glfw3native.h"

class Entity;

class TransformComponent : public Component
{
private:
    Vector3 m_position;
    Vector3 m_rotation;
    Vector3 m_scale;

    Entity* m_owner;
public:
    TransformComponent(Entity* _owner);
    TransformComponent(Vector3 _pos, Entity* _owner);
    TransformComponent(Vector3 _pos, Vector3 _rot, Entity* _owner);
    TransformComponent(Vector3 _pos, Vector3 _rot, Vector3 _scale, Entity* _owner);
    
    const Vector3& GetPosition() const;
    const Vector3& GetRotation() const;
    const Vector3& GetScale() const;
    Entity* GetOwner() const;

    void SetOwner(Entity* _owner);
    void SetPosition(const Vector3& _pos);
    void SetRotation(const Vector3& _rot);
    void SetScale(const Vector3& _scale);

    void ShowGuiDetails() override;

    void Activate() override{};
    void Tick() override {};
    void Deactivate() override{};
};
