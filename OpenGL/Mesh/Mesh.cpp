#include "Mesh.h"

#include <stdexcept>

#include "../Material/Material.h"
#include "../World/World.h"
#include "../Entities/Camera.h"
#include "../Shaders/Shader.h"
#include "../Buffers/Buffer.h"
#include "../Vertex/Vertex.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../../Dependencies/include/tinyobjloader-release/tiny_obj_loader.h"

Mesh::Mesh(Material* _material, Buffer* _buffer) :
    m_material(_material),
    m_buffer(_buffer)
{
    
}

std::vector<Mesh*> Mesh::Load(const char* _filename)
{
    std::vector<Mesh*> meshes;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;
    
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, _filename, "data/Models/"))
    {
        throw std::runtime_error(warn + err);
    }

    std::string texRoute = "data/Textures/";
    unsigned int materialIndex = 0;
    for (const auto& shape : shapes) {
        Shader* shader = Shader::Load("Data/Shaders/LightShader/VertexShader.glsl", "Data/Shaders/LightShader/FragmentShader.glsl");
        std::string materialName = std::string(materials[materialIndex].name + " Material");
        Material* material = new Material(shader, materialName, Vector3(1.0f, 1.0f, 1.0f),
                                          Vector3(1.0f, 1.0f, 1.0f));

        if(materials[materialIndex].diffuse_texname != "")
        {
            material->AddTexture(Texture::Load((texRoute + materials[materialIndex].diffuse_texname).c_str()));
        }
        
        else
        {
            material->AddTexture(Texture::Load("Data/Textures/DefaultTexture.jpg"));
        }

        if(materials[materialIndex].specular_texname != "")
        {
            material->AddTexture(Texture::Load((texRoute + materials[materialIndex].specular_texname).c_str()));
        }

        if(materials[materialIndex].emissive_texname != "")
        {
            material->AddTexture(Texture::Load((texRoute + materials[materialIndex].emissive_texname).c_str()));
        }

        ++materialIndex;
        
        std::vector<Vertex> tempVertices;
        std::vector<unsigned int> tempIndices;
        for (const auto& index : shape.mesh.indices) {
            Vertex* vertexAux = new Vertex();
            vertexAux->m_position.x = attrib.vertices[3 * index.vertex_index + 0];
            vertexAux->m_position.y = attrib.vertices[3 * index.vertex_index + 1];
            vertexAux->m_position.z = attrib.vertices[3 * index.vertex_index + 2];
            
            vertexAux->m_normal.x = attrib.normals[3* index.normal_index + 0];
            vertexAux->m_normal.y = attrib.normals[3* index.normal_index + 1];
            vertexAux->m_normal.z = attrib.normals[3* index.normal_index + 2];
            
            vertexAux->m_tex.x = attrib.texcoords[2 *
            index.texcoord_index + 0];
            vertexAux->m_tex.y = attrib.texcoords[2 *
            index.texcoord_index + 1];
            
            tempVertices.push_back(*vertexAux);
            tempIndices.push_back(tempIndices.size());
        }
        Buffer* buffer = new Buffer(tempVertices, tempIndices);
        meshes.push_back(new Mesh(material, buffer));
    }
    return meshes;
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

void Mesh::Prepare(const glm::mat4& _matrix)
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
