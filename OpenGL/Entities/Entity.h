#pragma once

#include <string>

#include "../../Math/Vector3/Vector3.h"

class Material;
class Buffer;

class Entity
{
protected:
    Material* m_material;
    Vector3 m_position;
    Vector3 m_rotation;
    Vector3 m_scale;
    Buffer* m_buffer;

    std::string m_name;

    bool m_GUIActive = false;
public:
    Entity();
    Entity(Material* _material);
    Entity(Material* _material, const std::string& _name);
    
    Vector3 GetPosition() const;
    Vector3 GetRotation() const;
    Vector3 GetScale() const;
    std::string GetName() const;
    Material* GetMaterial() const;

    virtual void SetPosition(const Vector3& _position);
    virtual void SetRotation(const Vector3& _rotation);
    virtual void SetScale(const Vector3& _scale);
    void SetBuffer(Buffer* buffer);
    void SetGuiActtive(bool _value);

    virtual void ShowGUIDetails();

    void Draw();
};
