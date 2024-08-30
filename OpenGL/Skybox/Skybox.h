#pragma once
#include <vector>

class Buffer;
class Material;
class Vertex;

class Skybox
{
private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    Material* m_material;
    
    Buffer* m_buffer;

public:
    Skybox();
    Skybox(Material* _mat);

    void Draw();
};
