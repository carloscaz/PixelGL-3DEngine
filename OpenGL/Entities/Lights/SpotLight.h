#pragma once
#include "Light.h"

class SpotLight : public Light
{
private:
    float m_constant;
    float m_linear;
    float m_quadratic;
    Vector3 m_direction;
    float m_cutOff;
    float m_outerCutOff;
public:
    SpotLight(Material* _material, std::string& _name);
    SpotLight(std::string& _name, Mesh* _mesh);

    Vector3 GetLightDirection();
    float GetLightCutOff();
    float GetOuterLightCutOff();
    float GetLightConstant();
    float GetLightLinear();
    float GetLightQuadratic();
    void Prepare() override;

    void ShowGUIDetails() override;
};
