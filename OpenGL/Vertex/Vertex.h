#pragma once
#include "../../Math/Vector3/Vector3.h"
#include "../../Math/Vector2/Vector2.h"

class Vertex
{
public:
    Vector3 m_position;
    Vector3 m_color;
    Vector2 m_tex;
    
    Vertex();
    Vertex(const Vector3& _pos);
    Vertex(const Vector3& _pos, const Vector3& _color);
    Vertex(const Vector3& _pos, const Vector3& _color, const Vector2& _tex);
};
