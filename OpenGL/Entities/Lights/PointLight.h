#pragma once
#include "Light.h"

class PointLight : public Light
{
private:
    float m_constant;
    float m_linear;
    float m_quadratic;
public:
    PointLight(Material* _material, std::string& _name);

    float GetLightConstant();
    float GetLightLinear();
    float GetLightQuadratic();
    
    void Prepare() override;
    void ShowGUIDetails() override;
};
