#pragma once

#include <string>
#include <vector>

#include "../../Math/Vector3/Vector3.h"

class Mesh;
class Material;
class Buffer;

class Entity
{
protected:
    Vector3 m_position;
    Vector3 m_rotation;
    Vector3 m_scale;

    std::string m_name;

    std::vector<Mesh*> m_meshes;

    bool m_GUIActive = false;
public:
    Entity();
    Entity(Material* _material);
    Entity(Material* _material, const std::string& _name);
    Entity(const std::string& _name, Mesh* _mesh);
    Entity(const std::string& _name, const std::vector<Mesh*>& _meshes);
    
    Vector3 GetPosition() const;
    Vector3 GetRotation() const;
    Vector3 GetScale() const;
    std::string GetName() const;

    virtual void SetPosition(const Vector3& _position);
    virtual void SetRotation(const Vector3& _rotation);
    virtual void SetScale(const Vector3& _scale);
    void SetGuiActtive(bool _value);

    virtual void ShowGUIDetails();

    virtual void Draw();
};
