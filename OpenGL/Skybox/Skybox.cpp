#include "Skybox.h"

#include <glad/glad.h>

#include "../Vertex/Vertex.h"
#include "../../Math/Vector3/Vector3.h"
#include "../Buffers/Buffer.h"
#include "../Material/Material.h"

Skybox::Skybox(Material* _mat)
{
    m_vertices =
    {
        Vertex(Vector3(-1.0f, 1.0f, -1.0f)), // 0
        Vertex(Vector3(-1.0f, -1.0f, -1.0f)), // 1
        Vertex(Vector3(1.0f, -1.0f, -1.0f)), // 2
        Vertex(Vector3(1.0f, 1.0f, -1.0f)), // 3
        Vertex(Vector3(-1.0f, 1.0f, 1.0f)), // 4
        Vertex(Vector3(-1.0f, -1.0f, 1.0f)), // 5
        Vertex(Vector3(1.0f, -1.0f, 1.0f)), // 6
        Vertex(Vector3(1.0f, 1.0f, 1.0f)) // 7
    };

    m_indices =
    {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        4, 5, 1,
        1, 0, 4,
        3, 2, 6,
        6, 7, 3,
        4, 0, 3,
        3, 7, 4,
        1, 5, 6,
        6, 2, 1
    };

    m_buffer = new Buffer(m_vertices, m_indices);

    m_material = _mat;
}

Skybox::~Skybox()
{
    m_vertices.clear();
    m_indices.clear();
    m_material = nullptr;
    delete m_buffer;
}

//Draw skybox in the world
void Skybox::Draw() const
{
    glDepthFunc(GL_LEQUAL);
    
    //Prepare skybox material properties
    m_material->Prepare();

    //Draw skybox
    m_buffer->Draw();
    
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}
