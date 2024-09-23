#pragma once
#include "../Component.h"
#include "../../../Math/Vector3/Vector3.h"

class PhysicComponent : public Component
{
private:
    //State variable to set the value before start simulate world
    float m_previousMass;
    bool m_previousGravity;
    
    Vector3 m_velocity;
    Vector3 m_acceleration;
    Vector3 m_Forces;
    
    float m_mass = 1.0f;
    
    bool m_gravity = true;
    
    void SetNewPosition(float _deltaTime); //Change position based in velocity
    void CalcAcceleration(float _deltaTime); //Calc acceleration of the body
public:
    PhysicComponent();
    ~PhysicComponent() override {};
    
    void ShowGuiDetails() override;

    void Init() override;
    void Activate() override{};
    void Tick(float _deltaTime) override;
    void Deactivate() override{};
    void End() override;

};
