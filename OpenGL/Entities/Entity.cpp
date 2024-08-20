#include "Entity.h"

#include "../Buffers/Buffer.h"
#include "../Material/Material.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Shaders/Shader.h"
#include "../GlUtils.h"
#include "ImGui/imgui.h"

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

void Entity::Draw()
{
    m_material->Prepare();
    
    float fov = 45.0f;
    // float rot = 20.0f;
    // ImGui::Begin("Scene cofig");
    // ImGui::Text("CameraFov:");
    // ImGui::SliderFloat("Fov", &fov, 0.0f, 100.0f);
    // ImGui::Text("Position:");
    // ImGui::DragFloat3("Position", &m_position.x, 0.05f);
    // ImGui::Text("Rotation:");
    // ImGui::DragFloat3("Rotation", &m_rotation.x, 0.2f, 0.0f, 360.0f);
    // ImGui::Text("Scale:");
    // ImGui::DragFloat3("Scale", &m_scale.x, 0.2f);
    // ImGui::End();
    
    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(fov), (float)windowWidth/(float)windowHeight, 0.1f, 100.0f);

    glm::mat4 m_viewMatrix = glm::mat4(1.0f);
    m_viewMatrix = lookAt(glm::vec3(0, 0, 5), glm::vec3(0,0,0),
                         glm::vec3(0, 1, 0));

    glm::mat4 m_modelMatrix = glm::mat4(1.0f);
    m_modelMatrix = translate(m_modelMatrix, glm::vec3(m_position.x, m_position.y, m_position.z));
    m_modelMatrix = rotate(m_modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_modelMatrix = rotate(m_modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_modelMatrix = rotate(m_modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_modelMatrix = scale(m_modelMatrix, glm::vec3(m_scale.x, m_scale.y, m_scale.z));

    m_material->GetShader()->SetMatrix("projection", proj);
    m_material->GetShader()->SetMatrix("view", m_viewMatrix);
    m_material->GetShader()->SetMatrix("model", m_modelMatrix);

    m_buffer->Draw();


}
