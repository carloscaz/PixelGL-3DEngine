#pragma once
#include "Material.h"

class SkyboxMaterial : public Material
{
public:
    SkyboxMaterial(Texture* _tex, Shader* _shader);
    void Prepare() override;
};
