#include "Camera.h"

#include "../../OpenGL/GlUtils.h"
#include "../../EditorUI/GUIManager/GUIManager.h"
#include "../Shaders/Shader.h"

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
    m_viewMatrix = lookAt(glm::vec3(m_position.x, m_position.y, m_position.z), glm::vec3(glm::vec3(0,0,0)),
                         glm::vec3(0, 1, 0));

    _shader->UseShader();
    _shader->SetMatrix("view", m_viewMatrix);
    _shader->SetMatrix("projection", proj);
    
}

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;
void Camera::Tick()
{
    if(glfwGetMouseButton(GUIManager::GetInstance()->GetGlFWwindow(), GLFW_MOUSE_BUTTON_RIGHT))
    {
        if(glfwGetKey(GUIManager::GetInstance()->GetGlFWwindow(), GLFW_KEY_W))
        {
            m_position.z -= ( 0.1f * 0.016f);
        }
    
        if(glfwGetKey(GUIManager::GetInstance()->GetGlFWwindow(), GLFW_KEY_S))
        {
            m_position.z += ( 0.1f * 0.016f);
        }
    
        if(glfwGetKey(GUIManager::GetInstance()->GetGlFWwindow(), GLFW_KEY_A))
        {
            m_position.x -= ( 0.1f * 0.016f);
        }
    
        if(glfwGetKey(GUIManager::GetInstance()->GetGlFWwindow(), GLFW_KEY_D))
        {
            m_position.x += ( 0.1f * 0.016f);
        }
    
        if(glfwGetKey(GUIManager::GetInstance()->GetGlFWwindow(), GLFW_KEY_Q))
        {
            m_position.y -= ( 0.1f * 0.016f);
        }
    
        if(glfwGetKey(GUIManager::GetInstance()->GetGlFWwindow(), GLFW_KEY_E))
        {
            m_position.y += ( 0.1f * 0.016f);
        }
    }
}

void Camera::UpdateDirection(double xpos, double ypos)
{
    // if (firstMouse)
    // {
    //     lastX = xpos;
    //     lastY = ypos;
    //     firstMouse = false;
    // }
    //
    // float xoffset = xpos - lastX;
    // float yoffset = lastY - ypos; 
    // lastX = xpos;
    // lastY = ypos;
    //
    // float sensitivity = 0.1f;
    // xoffset *= sensitivity;
    // yoffset *= sensitivity;
    //
    // yaw   += xoffset;
    // pitch += yoffset;
    //
    // if(pitch > 89.0f)
    //     pitch = 89.0f;
    // if(pitch < -89.0f)
    //     pitch = -89.0f;
    //
    // glm::vec3 direction;
    // direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    // direction.y = sin(glm::radians(pitch));
    // direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    // cameraFront = glm::normalize(direction);
}  
