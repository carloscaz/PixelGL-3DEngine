#include "Vector3.h"

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f)
{}

Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{}

Vector3 Vector3::operator+(const Vector3& _vector)
{
    return Vector3(x + _vector.x, y + _vector.y, z + _vector.z);
}

Vector3 Vector3::operator+=(const Vector3& _vector)
{
    this->x += _vector.x;
    this->y += _vector.y;
    this->z += _vector.z;
    return (*this);
}

Vector3 Vector3::operator-=(const Vector3& _vector)
{
    this->x -= _vector.x;
    this->y -= _vector.y;
    this->z -= _vector.z;
    return (*this);
}

Vector3 Vector3::operator-(const Vector3& _vector)
{
    return Vector3(z - _vector.x, y - _vector.y, z - _vector.z);
}

Vector3 Vector3::operator*(float _number)
{
    return Vector3(x * _number, y * _number, z * _number);
}

Vector3 Vector3::operator/(float _number)
{
    return Vector3(x / _number, y / _number, z / _number);
}
