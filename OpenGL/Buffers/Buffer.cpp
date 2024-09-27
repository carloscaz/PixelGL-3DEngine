#include "Buffer.h"

#include <vector>
#include "../../Dependencies/include/glad/glad.h"

#include "../Vertex/Vertex.h"

Buffer::Buffer()
{
}

Buffer::Buffer(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices) : m_vertices(_vertices), m_indices (_indices) 
{
    //Generate VAO, VBO and EBO and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //Setting VBO and EBO with data
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

    //Link position of the vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, m_position));
    glEnableVertexAttribArray(0);

    //Link texture coordinates of the vertex
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, m_tex));
    glEnableVertexAttribArray(1);

    //Link normal of the vertex
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_normal));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

}

Buffer::~Buffer()
{
    m_vertices.clear();
    m_indices.clear();
}

//Draw buffer
void Buffer::Draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
}
