#pragma once
#include <vector>

class Vertex;

class Buffer
{
private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
public:
    unsigned int VBO, EBO, VAO;
    Buffer();
    Buffer(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices);
    ~Buffer();

    void Draw();
};
