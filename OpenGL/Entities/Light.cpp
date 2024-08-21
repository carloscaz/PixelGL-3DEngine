#include "Light.h"

Light::Light(Material* _material, const std::string& _name) : Entity(_material, _name)
{
    m_scale = Vector3(0.2f, 0.2f, 0.2f);
}
