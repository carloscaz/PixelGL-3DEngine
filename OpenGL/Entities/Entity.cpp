#include "Entity.h"

#include "../Buffers/Buffer.h"
#include "../Material/Material.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "../Mesh/Mesh.h"
#include "../Shaders/Shader.h"
#include "../World/World.h"
#include "ImGui/imgui.h"

Entity::Entity() : m_position(Vector3()), m_rotation(Vector3()), m_scale(Vector3(1,1,1)), m_name("Entity")
{
}

Entity::Entity(Material* _material) : m_position(Vector3()), m_rotation(Vector3()), m_scale(Vector3(1,1,1)), m_name("Entity")
{
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

Vector3 Entity::GetPosition() const
{
    return m_position;
}

Vector3 Entity::GetRotation() const
{
    return m_rotation;
}

Vector3 Entity::GetScale() const
{
    return m_scale;
}

std::string Entity::GetName() const
{
    return m_name;
}

void Entity::SetPosition(const Vector3& _position)
{
    m_position = _position;
}

void Entity::SetRotation(const Vector3& _rotation)
{
    m_rotation = _rotation;
}

void Entity::SetScale(const Vector3& _scale)
{
    m_scale = _scale;
}


void Entity::SetGuiActtive(bool _value)
{
    m_GUIActive = _value;
}

void Entity::ShowGUIDetails()
{
    int meshIndex = 0;
    if (ImGui::CollapsingHeader("Object Meshes"))
    {
        for(Mesh* mesh : m_meshes)
        {
            if (ImGui::CollapsingHeader(std::string(("Mesh ") + std::to_string(meshIndex)).c_str()))
            {
                //mesh->GetMaterial()->ShowGUIDetails();
            }
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
    m_modelMatrix = translate(m_modelMatrix, glm::vec3(m_position.x, m_position.y, m_position.z));
    m_modelMatrix = rotate(m_modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_modelMatrix = rotate(m_modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_modelMatrix = rotate(m_modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_modelMatrix = scale(m_modelMatrix, glm::vec3(m_scale.x, m_scale.y, m_scale.z));
    
    // m_material->GetShader()->SetMatrix("model", m_modelMatrix);
    //
    // m_buffer->Draw();

    for(Mesh* mesh : m_meshes)
    {
        mesh->Prepare(m_modelMatrix);
    }
    
}
