#include "State.h"
#include "../../OpenGL/GlUtils.h"
State* State::m_instance = nullptr;

State::State()
{
    float fov = 45.0f;
    
    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(fov), (float)windowWidth/(float)windowHeight, 0.1f, 100.0f);

    m_projMatrix = proj;
}

State* State::GetIntance()
{
    if(!m_instance)
    {
        m_instance = new State();
    }

    return m_instance;
}

glm::mat4 State::GetProjectionMatrix() const
{
    return m_projMatrix;
}

void State::SetProjectionMatrix(const glm::mat4& _matrix)
{
    m_projMatrix = _matrix;
}
