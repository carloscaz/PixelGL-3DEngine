#pragma once
#include "../Entity.h"

class Light : public Entity
{
protected:
    Vector3 m_color;
    Vector3 m_diffuse;
    Vector3 m_specular;
    float m_strength;
public:
    Light(Material* _material, const std::string& _name);
    ~Light() override;
    
    void ShowGUIDetails() override;

    Vector3 GetLightColor() const;
    Vector3 GetLightDiffuse() const;
    Vector3 GetLightSpecular() const;
    float GetLightStrength() const;

    virtual void Prepare();
};

