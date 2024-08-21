#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <glad/glad.h>

#include "../../Math/Vector3/Vector3.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


Shader::Shader()
{
}

Shader* Shader::Load(const char* _vertexFilename, const char* _fragmentFilename)
{
    Shader* newShader = new Shader();
    //Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    //Ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        //Open files
        vShaderFile.open(_vertexFilename);
        fShaderFile.open(_fragmentFilename);
        std::stringstream vShaderStream, fShaderStream;
        
        //Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        //Close file handlers
        vShaderFile.close();
        fShaderFile.close();
        
        //Convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    
    newShader->vertexShaderSource = vertexCode.c_str();
    newShader->fragmentShaderSource = fragmentCode.c_str();

    const char* vShaderCode =  vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    //Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);

    //Check for shader compile errors in vertex shader
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);

    //Check for shader compile errors in fragment shader
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Create Shader
    newShader->m_id = glCreateProgram();
    glAttachShader(newShader->m_id, vertexShader);
    glAttachShader(newShader->m_id, fragmentShader);
    glLinkProgram(newShader->m_id);
    //Check for linking errors
    glGetProgramiv(newShader->m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(newShader->m_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return newShader;
}

void Shader::UseShader()
{
    glUseProgram(m_id);
}

void Shader::SetVec3(const char* _loc, const Vector3& _value)
{
    glUseProgram(m_id);
    unsigned int loc = glGetUniformLocation(m_id, _loc);
    glUniform3f(loc, _value.x, _value.y, _value.z);
}

void Shader::SetMatrix(const char* _location, const glm::mat4& _matrix)
{
    glUseProgram(m_id);
    unsigned int loc = glGetUniformLocation(m_id, _location);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(_matrix));
}

void Shader::SetFloat(const char* _location, float _value)
{
    glUseProgram(m_id);
    unsigned int loc = glGetUniformLocation(m_id, _location);
    glUniform1f(loc, _value);
}

void Shader::SetInt(const char* _location, int _value)
{
    glUseProgram(m_id);
    unsigned int loc = glGetUniformLocation(m_id, _location);
    glUniform1i(loc, _value);
}

