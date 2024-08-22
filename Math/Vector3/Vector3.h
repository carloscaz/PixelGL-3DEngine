#pragma once

class Vector3
{
public:
    float x, y, z;
    Vector3();
    Vector3(float _x, float _y, float _z);

    Vector3 operator +=(const Vector3& _vector);
    Vector3 operator-=(const Vector3& _vector);
    Vector3 operator*(float _number);
};
