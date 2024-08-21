#pragma once
#include <glm/detail/type_mat.hpp>

class Vector3;

class Shader
{
protected:
    const char* vertexShaderSource;
    const char* fragmentShaderSource;
    
    unsigned int VertexShader;
    unsigned int FragmentShader;
    int retCode;
    char errorLog[1024];

    unsigned int m_id;
    
    Shader();
public:
    static Shader* Load(const char* _vertexFilename, const char* _fragmentFilename);

    void UseShader();
    void SetVec3(const char* _loc, const Vector3& _value);
    void SetMatrix(const char* _location, const glm::mat4& _matrix);
    void SetFloat(const char* _location, float _value);
};
