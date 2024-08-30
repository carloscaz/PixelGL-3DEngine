#include "Entity.h"

#include "../Buffers/Buffer.h"
#include "../Material/Material.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "../Components/Component.h"
#include "../Components/TransformComponent.h"
#include "../Components/Physics/PhysicComponent.h"
#include "../Mesh/Mesh.h"
#include "../Shaders/Shader.h"
#include "../World/World.h"
#include "ImGui/imgui.h"

Entity::Entity() : m_position(Vector3()), m_rotation(Vector3()), m_scale(Vector3(1,1,1)), m_name("Entity")
{
    m_components.push_back(new TransformComponent(Vector3(0,0,0), Vector3(0,0,0), Vector3(1,1,1), this));
}

Entity::Entity(Material* _material) : m_position(Vector3()), m_rotation(Vector3()), m_scale(Vector3(1,1,1)), m_name("Entity")
{
    m_components.push_back(new TransformComponent(Vector3(0,0,0), Vector3(0,0,0), Vector3(1,1,1), this));
}

Entity::Entity(Material* _material, const std::string& _name) : Entity(_material)
{
    m_name = _name;
}

Entity::Entity(const std::string& _name, Mesh* _mesh) :
    Entity(nullptr, _name)
{
    m_meshes.push_back(_mesh);
}

Entity::Entity(const std::string& _name, const std::vector<Mesh*>& _meshes) :
    Entity(nullptr, _name)
{
    m_meshes = _meshes;
}

const Vector3& Entity::GetPosition()
{
    return GetComponent<TransformComponent>()->GetPosition();
}

const Vector3& Entity::GetRotation()
{
    return GetComponent<TransformComponent>()->GetRotation();
}

const Vector3& Entity::GetScale()
{
    return GetComponent<TransformComponent>()->GetScale();
}

std::string Entity::GetName() const
{
    return m_name;
}

bool Entity::GetIsSelectable()
{
    return m_isSelectable;
}

void Entity::SetPosition(const Vector3& _position)
{
    GetComponent<TransformComponent>()->SetPosition(_position);
}

void Entity::SetRotation(const Vector3& _rotation)
{
    GetComponent<TransformComponent>()->SetRotation(_rotation);
}

void Entity::SetScale(const Vector3& _scale)
{
    GetComponent<TransformComponent>()->SetScale(_scale);
}


void Entity::SetGuiActtive(bool _value)
{
    m_GUIActive = _value;
}

void Entity::SetIsSelectable(bool _value)
{
    m_isSelectable = _value;
}

void Entity::AddComponent(Component* _component)
{
    m_components.push_back(_component);
}

void Entity::ShowGUIDetails()
{
    if(ImGui::CollapsingHeader("Components"))
    {
        ImGui::Indent(10.0f);
        for(Component* component : m_components)
        {
            component->ShowGuiDetails();
        }
        ImGui::Unindent(10.0f);

        ImGui::Separator();
        if (ImGui::SmallButton("Add New Component"))
        {
            ImGui::OpenPopup("Components List");
        }

        if (ImGui::BeginPopup("Components List"))
        {
            if (ImGui::MenuItem("Physics Component"))
            {
                AddComponent(new PhysicComponent());
            }
            ImGui::EndPopup();
        }
        
    }
    
    ImGui::Separator();
    int meshIndex = 0;
    if (ImGui::CollapsingHeader("Object Meshes"))
    {
        for(Mesh* mesh : m_meshes)
        {
            ImGui::Indent(10.0f);
            if (ImGui::CollapsingHeader(std::string(("Mesh ") + std::to_string(meshIndex)).c_str()))
            {
                ImGui::Indent(10.0f);
                mesh->GetMaterial()->ShowGUIDetails(meshIndex);
                ImGui::Unindent(10.0f);
            }
            ImGui::Unindent(10.0f);
            ++meshIndex;
            
        }
    }

    
    
   

}

void Entity::Draw()
{
    // if(m_material)
    // {
    //     m_material->Prepare();
    // }
    //
    // World::GetInstance()->GetActiveCamera()->Prepare(m_material->GetShader());
    
    glm::mat4 m_modelMatrix = glm::mat4(1.0f);
    m_modelMatrix = translate(m_modelMatrix, glm::vec3(GetComponent<TransformComponent>()->GetPosition().x, GetComponent<TransformComponent>()->GetPosition().y, GetComponent<TransformComponent>()->GetPosition().z));
    m_modelMatrix = rotate(m_modelMatrix, glm::radians(GetComponent<TransformComponent>()->GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_modelMatrix = rotate(m_modelMatrix, glm::radians(GetComponent<TransformComponent>()->GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_modelMatrix = rotate(m_modelMatrix, glm::radians(GetComponent<TransformComponent>()->GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_modelMatrix = scale(m_modelMatrix, glm::vec3(GetComponent<TransformComponent>()->GetScale().x, GetComponent<TransformComponent>()->GetScale().y, GetComponent<TransformComponent>()->GetScale().z));
    
    // m_material->GetShader()->SetMatrix("model", m_modelMatrix);
    //
    // m_buffer->Draw();

    for(Mesh* mesh : m_meshes)
    {
        mesh->Prepare(m_modelMatrix);
    }
    
}
