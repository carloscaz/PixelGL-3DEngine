#pragma once
#include <glm/detail/type_mat.hpp>

class Buffer;
class Material;

class Mesh
{
private:
    Material* m_material;
    Buffer* m_buffer;
public:
    Mesh(Material* _material, Buffer* _buffer);

    Material* GetMaterial() const;
    Buffer* GetBuffer() const;

    void SetModelMatrix(glm::mat4 _matrix);
    void Prepare(glm::mat4 _matrix);
    void Draw();
};
