#include "SkyboxMaterial.h"

#include <glm/gtc/matrix_transform.hpp>

#include "../include/glm/glm.hpp"

#include "../GlUtils.h"
#include "../World/World.h"
#include "../Shaders/Shader.h"
#include "../Entities/Camera.h"
#include "../Entities/Lights/DirectionalLight.h"

SkyboxMaterial::SkyboxMaterial(Texture* _tex, Shader* _shader) :
    Material(_tex, _shader)
{}

void SkyboxMaterial::Prepare()
{
    //Activate shader
    m_shader->UseShader();

    //Calculate MVP for shader
    Vector3 camPos = World::GetInstance()->GetActiveCamera()->GetPosition();

    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(45.0f), (float)windowWidth/(float)windowHeight, 0.1f, 100.0f);
    
    glm::mat4 m_viewMatrix = glm::mat4(1.0f);
    m_viewMatrix = lookAt(glm::vec3(camPos.x, camPos.y, camPos.z), glm::vec3(glm::vec3(camPos.x,camPos.y,camPos.z) + World::GetInstance()->GetActiveCamera()->GetCameraFront()),
                         glm::vec3(0, 1, 0));

    glm::mat3 view = glm::mat4(glm::mat3(m_viewMatrix));

    //Setting light properties of shader
    m_shader->UseShader();
    m_shader->SetFloat("lightStrength", World::GetInstance()->GetDirectionaLight()->GetLightStrength());
    m_shader->SetVec3("lightColor", World::GetInstance()->GetDirectionaLight()->GetLightDiffuse());
    m_shader->SetInt("skybox", 0);
    m_shader->SetMatrix("view", view);
    m_shader->SetMatrix("projection", proj);
}
