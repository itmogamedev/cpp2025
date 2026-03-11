#pragma once

#ifdef HW1DLL_EXPORTS
#define HW1DLL_API __declspec(dllexport)
#else
#define HW1DLL_API __declspec(dllimport)
#endif

#include <iostream>

struct HW1DLL_API Vec3
{
    float x, y, z;

    Vec3();
    Vec3(float x, float y, float z);

    Vec3 operator+(const Vec3& v) const;
    Vec3 operator-(const Vec3& v) const;
    Vec3 operator*(float s) const;

    float dot(const Vec3& v) const;
    Vec3 cross(const Vec3& v) const;

    float length() const;
    Vec3 normalize() const;
};

HW1DLL_API std::ostream& operator<<(std::ostream& os, const Vec3& v);