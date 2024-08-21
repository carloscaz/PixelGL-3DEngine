#include "Camera.h"

#include "../Shaders/Shader.h"
#include "../../OpenGL/GlUtils.h"

Camera::Camera() : m_cameraFov(45.0f)
{
}

glm::mat4 Camera::GetViewMatrix() const
{
    return m_viewMatrix;
}

void Camera::SetViewMatrix(const glm::mat4& _matrix)
{
    m_viewMatrix = _matrix;
}

void Camera::SetCameraFov(float _fov)
{
    m_cameraFov = _fov;
}

void Camera::Prepare(Shader* _shader)
{
    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(m_cameraFov), (float)windowWidth/(float)windowHeight, 0.1f, 100.0f);
    
    glm::mat4 m_viewMatrix = glm::mat4(1.0f);
    m_viewMatrix = lookAt(glm::vec3(m_position.x, m_position.y, m_position.z), glm::vec3(0,0,0),
                         glm::vec3(0, 1, 0));

    _shader->UseShader();
    _shader->SetMatrix("view", m_viewMatrix);
    _shader->SetMatrix("projection", proj);
    
}
