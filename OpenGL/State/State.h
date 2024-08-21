#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class State
{
private:
    static State* m_instance;
    State();

    glm::mat4 m_projMatrix;
public:
    static State* GetIntance();
    glm::mat4 GetProjectionMatrix() const;
    void SetProjectionMatrix(const glm::mat4& _matrix);
};
