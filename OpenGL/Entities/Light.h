#pragma once
#include "Entity.h"

class Light : public Entity
{
public:
    Light(Material* _material, const std::string& _name);
    void SetScale(const Vector3& _scale) override{};
    void SetRotation(const Vector3& _rotation) override{};
    void ShowGUIDetails() override{};
};
