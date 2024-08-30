#pragma once
#include "../Component.h"

class PhysicComponent : public Component
{
public:
    PhysicComponent();
    
    void ShowGuiDetails() override;
    
    void Activate() override{};
    void Tick() override {};
    void Deactivate() override{};
};
