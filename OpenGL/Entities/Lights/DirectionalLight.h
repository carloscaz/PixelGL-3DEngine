#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
private:
    Vector3 m_direction;
public:
    DirectionalLight(Material* _material);
    void Prepare() override;

    Vector3 GetLightDirection() const;
    void Draw() override {};

    void ShowGUIDetails() override;
};
