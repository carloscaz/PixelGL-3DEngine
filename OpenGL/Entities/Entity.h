#pragma once

#include <string>
#include <vector>

#include "../../Math/Vector3/Vector3.h"
#include "../Components/Component.h"

class Component;
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
    std::vector<Component*> m_components;

    bool m_GUIActive = false;
    bool m_isSelectable = false;
public:
    Entity();
    Entity(Material* _material);
    Entity(Material* _material, const std::string& _name);
    Entity(const std::string& _name, Mesh* _mesh);
    Entity(const std::string& _name, const std::vector<Mesh*>& _meshes);
    
    const Vector3& GetPosition();
    const Vector3& GetRotation();
    const Vector3& GetScale();
    std::string GetName() const;
    bool GetIsSelectable();

    virtual void SetPosition(const Vector3& _position);
    virtual void SetRotation(const Vector3& _rotation);
    virtual void SetScale(const Vector3& _scale);
    void SetGuiActtive(bool _value);
    void SetIsSelectable(bool _value);

    void AddComponent(Component* _component);
    template <class T>
    T* GetComponent();

    virtual void ShowGUIDetails();

    virtual void Draw();
};

template <class T>
T* Entity::GetComponent()
{
    for(Component* component : m_components)
    {
        T* comp = dynamic_cast<T*>(component);
        if(comp)
        {
            return comp;
        }
    }

    return nullptr;
}
