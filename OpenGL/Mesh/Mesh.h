#pragma once
#include <vector>
#include "../../Dependencies/include/glm/detail/type_mat.hpp"

class Buffer;
class Material;

class Mesh
{
private:
    Material* m_material;
    Buffer* m_buffer;
public:
    Mesh(Material* _material, Buffer* _buffer);
    static std::vector<Mesh*> Load(const char* _filename);
    //static std::vector<Mesh*> Load(const char* _filename);

    Material* GetMaterial() const;
    Buffer* GetBuffer() const;

    void SetModelMatrix(glm::mat4 _matrix);
    void Prepare(const glm::mat4& _matrix);
    void Draw();
};
