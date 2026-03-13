#include "pch.h"
#include "VecLib.h"

// --- Конструкторы ---
Vec3::Vec3() : x(0), y(0), z(0) {}
Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

// --- Методы ---
float Vec3::Length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::Normalize() const
{
    float len = Length();
    if (len > 0.0f)
    {
        return Vec3(x / len, y / len, z / len);
    }
    return Vec3(0, 0, 0);
}

// --- Операторы ---
Vec3 Vec3::operator+(const Vec3& other) const
{
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const
{
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(float scalar) const
{
    return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 operator*(float scalar, const Vec3& vec)
{
    return vec * scalar;
}

std::ostream& operator<<(std::ostream& os, const Vec3& vec)
{
    os << "Vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

// --- Функции ---
float DotProduct(const Vec3& a, const Vec3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 CrossProduct(const Vec3& a, const Vec3& b)
{
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}