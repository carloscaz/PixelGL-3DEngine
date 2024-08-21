#pragma once
#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader;

class Camera : public Entity
{
private:
    glm::mat4 m_viewMatrix;
    float m_cameraFov;
public:
    Camera();

    glm::mat4 GetViewMatrix() const;
    void SetViewMatrix(const glm::mat4& _matrix);
    void SetCameraFov(float _fov);

    void Prepare(Shader* _shader);
};
