#include "Vector3.h"

const Vector3 Vector3::Up      = Vector3( 0, 1,  0);
const Vector3 Vector3::Down    = Vector3( 0,-1,  0);
const Vector3 Vector3::Right   = Vector3( 1, 0,  0);
const Vector3 Vector3::Left    = Vector3(-1, 0,  0);
const Vector3 Vector3::Forward = Vector3( 0, 0, -1);
const Vector3 Vector3::Back    = Vector3( 0, 0,  1);
const Vector3 Vector3::Zero    = Vector3( 0, 0,  0);
const Vector3 Vector3::One     = Vector3( 1, 1,  1);
//*/

Vector3::Vector3()
{
    x = y = z = 0.0f;
}

Vector3::Vector3(const glm::vec3 &v) : glm::vec3(v)
{
}

Vector3::Vector3(float a)
{
    x = y = z = a;
}

Vector3::Vector3(float x, float y, float z) : glm::vec3(x,y,z)
{
    this->x = x; this->y = y; this->z = z;
}

float Vector3::Length() const
{
    return float(glm::sqrt(x*x + y*y + z*z));
}

void Vector3::Normalize()
{
    float l = Length();
    x /= l;
    y /= l;
    z /= l;
}

Vector3 Vector3::Normalized() const
{
    Vector3 v(*this);
    v.Normalize();
    return v;
}

Vector3 Vector3::ToDegrees() const
{
    return Vector3(glm::degrees(glm::vec3(*this)));
}

Vector3 Vector3::ToRadians() const
{
    return Vector3(glm::radians(glm::vec3(*this)));
}

std::string Vector3::ToString() const
{
    return "(" + std::to_string(x) + ", " +
                 std::to_string(y) + ", " +
                 std::to_string(z) + ")";
}

float Vector3::Distance(const Vector3 &p) const
{
    return Vector3::Distance(*this, p);
}

void Vector3::OrthoNormalize(Vector3 &v1, Vector3 &v2)
{
    //Not sure if this is working...
    v1.Normalize();
    v2.Normalize();
    Vector3 aux = Vector3::Cross(v1, v2).Normalized();
    v2 = Vector3::Cross(aux, v1).Normalized();
}

Vector3 Vector3::Lerp(const Vector3 &v1,
                      const Vector3 &v2,
                      float progression)
{
    return Vector3(glm::mix(glm::vec3(v1), glm::vec3(v2), progression));
}

Vector3 Vector3::Abs() const
{
    return Vector3(glm::abs(x), glm::abs(y), glm::abs(z));
}

Vector3 Vector3::Abs(const Vector3 &v)
{
    return v.Abs();
}

Vector3 Vector3::Cross(const Vector3 &v1, const Vector3 &v2)
{
    return Vector3(glm::cross(glm::vec3(v1), glm::vec3(v2)));
}

float Vector3::Dot(const Vector3 &v1, const Vector3 &v2)
{
    return glm::dot(glm::vec3(v1), glm::vec3(v2));
}

float Vector3::Distance(const Vector3 &v1, const Vector3 &v2)
{
    return (v1 - v2).Length();
}







Vector3 operator+(const Vector3 & v1, const Vector3 &v2)
{
    return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}


Vector3 operator*(const Vector3 &v1, const Vector3 &v2)
{
    return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}


Vector3 operator-(const Vector3 &v)
{
    return Vector3(-v.x, -v.y, -v.z);
}


Vector3 operator*(float a, const Vector3 &v)
{
    return Vector3(a * v.x, a * v.y, a * v.z);
}


Vector3 operator*(const Vector3 &v, float a)
{
    return a * v;
}


Vector3 operator/(float a, const Vector3 &v)
{
    return Vector3(a / v.x, a / v.y, a / v.z);
}


Vector3 operator/(const Vector3 &v, float a)
{
    return Vector3(v.x / a, v.y / a, v.z / a);
}


Vector3 operator/(const Vector3 &v1, const Vector3 &v2)
{
    return Vector3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}


Vector3 &operator+=(Vector3 &lhs, const Vector3 &rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}


Vector3 &operator-=(Vector3 &lhs, const Vector3 &rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
}

Vector3 &operator*=(Vector3 &lhs, const Vector3 &rhs)
{
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    lhs.z *= rhs.z;
    return lhs;
}


Vector3 &operator/=(Vector3 &lhs, const Vector3 &rhs)
{
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
    lhs.z /= rhs.z;
    return lhs;
}


Vector3 operator+(float a, const Vector3 &v)
{
    return Vector3(a + v.x, a + v.y, a + v.z);
}


Vector3 operator+(const Vector3 &v, float a)
{
    return a + v;
}


Vector3 operator-(const Vector3 &v1, const Vector3 &v2)
{
    return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}


Vector3 operator-(const Vector3 &v, float a)
{
    return Vector3(v.x - a, v.y - a, v.z - a);
}


Vector3 operator-(float a, const Vector3 &v)
{
    return Vector3(a - v.x, a - v.y, a - v.z);
}


Vector3 &operator+=(Vector3 &lhs, float a)
{
    lhs.x += a;
    lhs.y += a;
    lhs.z += a;
    return lhs;
}


Vector3 &operator-=(Vector3 &lhs, float a)
{
    lhs.x -= a;
    lhs.y -= a;
    lhs.z -= a;
    return lhs;
}


Vector3 &operator*=(Vector3 &lhs, float a)
{
    lhs.x *= a;
    lhs.y *= a;
    lhs.z *= a;
    return lhs;
}


Vector3 &operator/=(Vector3 &lhs, float a)
{
    lhs.x /= a;
    lhs.y /= a;
    lhs.z /= a;
    return lhs;
}

