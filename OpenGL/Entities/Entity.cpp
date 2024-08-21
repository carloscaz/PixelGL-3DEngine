#include "Entity.h"

#include "../Buffers/Buffer.h"
#include "../Material/Material.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "../Shaders/Shader.h"
#include "../World/World.h"

Entity::Entity() : m_material(nullptr), m_position(Vector3()), m_rotation(Vector3()), m_scale(Vector3(1,1,1)), m_name("Entity")
{
}

Entity::Entity(Material* _material) : m_material(_material), m_position(Vector3()), m_rotation(Vector3()), m_scale(Vector3(1,1,1)), m_name("Entity")
{
}

Entity::Entity(Material* _material, const std::string& _name) : Entity(_material)
{
    m_name = _name;
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

Material* Entity::GetMaterial() const
{
    return m_material;
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

void Entity::SetBuffer(Buffer* buffer)
{
    m_buffer = buffer;
}

void Entity::SetGuiActtive(bool _value)
{
    m_GUIActive = _value;
}

void Entity::ShowGUIDetails()
{
    m_material->ShowGUIDetails();
}

void Entity::Draw()
{
    m_material->Prepare();
    
    World::GetInstance()->GetActiveCamera()->Prepare(m_material->GetShader());
    
    glm::mat4 m_modelMatrix = glm::mat4(1.0f);
    m_modelMatrix = translate(m_modelMatrix, glm::vec3(m_position.x, m_position.y, m_position.z));
    m_modelMatrix = rotate(m_modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_modelMatrix = rotate(m_modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_modelMatrix = rotate(m_modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_modelMatrix = scale(m_modelMatrix, glm::vec3(m_scale.x, m_scale.y, m_scale.z));
    
    m_material->GetShader()->SetMatrix("model", m_modelMatrix);

    m_buffer->Draw();


}
