#include "Vertex.h"

Vertex::Vertex() : m_position(Vector3()), m_color(Vector3()), m_tex(Vector2())
{}

Vertex::Vertex(const Vector3& _pos) : m_position(_pos), m_color(Vector3())
{}

Vertex::Vertex(const Vector3& _pos, const Vector3& _color) : m_position(_pos), m_color(_color),  m_tex(Vector2())
{}

Vertex::Vertex(const Vector3& _pos, const Vector3& _color, const Vector2& _tex): m_position(_pos), m_color(_color), m_tex(_tex)
{
}
