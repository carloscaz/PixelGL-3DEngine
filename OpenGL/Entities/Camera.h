#pragma once
#include "Entity.h"
#include "../../Dependencies/include/glm/glm.hpp"
#include "../../Dependencies/include/glm/gtc/matrix_transform.hpp"
#include "../../Dependencies/include/glm/gtc/type_ptr.hpp"

class Shader;

class Camera : public Entity
{
private:
    glm::mat4 m_viewMatrix;
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    float m_cameraFov;
public:
    Camera();

    glm::mat4 GetViewMatrix() const;
    void SetViewMatrix(const glm::mat4& _matrix);
    void SetCameraFov(float _fov);

    void Prepare(Shader* _shader);

    void Tick();
    
    void UpdateDirection(double xpos, double ypos);
};
