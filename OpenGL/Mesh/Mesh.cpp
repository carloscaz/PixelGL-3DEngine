#include "Mesh.h"

#include "../Material/Material.h"
#include "../World/World.h"
#include "../Entities/Camera.h"
#include "../Shaders/Shader.h"
#include "../Buffers/Buffer.h"

Mesh::Mesh(Material* _material, Buffer* _buffer) :
    m_material(_material),
    m_buffer(_buffer)
{
    
}

Material* Mesh::GetMaterial() const
{
    return m_material;
}

Buffer* Mesh::GetBuffer() const
{
    return m_buffer;
}

void Mesh::SetModelMatrix(glm::mat4 _matrix)
{
    
}

void Mesh::Prepare(glm::mat4 _matrix)
{
    m_material->Prepare();
    World::GetInstance()->GetActiveCamera()->Prepare(m_material->GetShader());
    m_material->GetShader()->SetMatrix("model", _matrix);
    m_buffer->Draw();
}

void Mesh::Draw()
{
    m_material->Prepare();
}
