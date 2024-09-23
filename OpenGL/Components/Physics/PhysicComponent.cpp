#include "PhysicComponent.h"

#include "../Transform/TransformComponent.h"
#include "../../Entities/Entity.h"
#include "ImGui/imgui.h"


PhysicComponent::PhysicComponent() :
m_previousMass(1.0f),
m_previousGravity(true)
{
    m_active = true;
}

//Physic component ImGui window
void PhysicComponent::ShowGuiDetails()
{
    if (ImGui::CollapsingHeader("RigidBody"))
    {
        //The component is active
        ImGui::Checkbox("Active", &m_active);

        //The component simulates gravity
        if(ImGui::Checkbox("Simulate Gravity", &m_gravity))
        {
            m_velocity.y = 0.0f;
        }

        //Mass of the component
        ImGui::Text("Mass");
        ImGui::InputFloat("##Mass", &m_mass);
        
        ImGui::Text("Linear Acceleration");
        ImGui::DragFloat3("##LinearAcceleration", &m_acceleration.x, 0.05f);
        
        ImGui::Text("Linear Velocity");
        ImGui::DragFloat3("##LinearVelocity", &m_velocity.x, 0.05f);
    }
}

//Save the data of the component before simulation
void PhysicComponent::Init()
{
    m_previousGravity = m_gravity;
    m_previousMass = m_mass;
    
    m_velocity = Vector3(0,0,0);
    m_acceleration = Vector3(0,0,0);
}

void PhysicComponent::Tick(float _deltaTime)
{
    //Reset all forces to zero
    m_Forces = Vector3(0,0,0);
    
    if(m_active)
    {
        CalcAcceleration(_deltaTime);
        SetNewPosition(_deltaTime);
    }
}

//Save the data of the component after simulation
void PhysicComponent::End()
{
    m_gravity = m_previousGravity;
    m_mass = m_previousMass;
}

//Calculate the acceleration of the entuty
void PhysicComponent::CalcAcceleration(float _deltaTime)
{
    //Add gravity force to the entity
    if(m_gravity)
    {
        Vector3 gravity = Vector3(0,-9.8f, 0) * m_mass;
        m_Forces += gravity;
    }
    m_acceleration = m_Forces / m_mass;
    m_velocity += m_acceleration * _deltaTime;
}

//Change position based in velocity
void PhysicComponent::SetNewPosition(float _deltaTime)  
{
    Vector3 pos = GetOwner()->GetComponent<TransformComponent>()->GetPosition();
    GetOwner()->GetComponent<TransformComponent>()->SetPosition(pos + (m_velocity * _deltaTime));
}
