#pragma once

#include <iostream>

#ifdef DLL1_EXPORTS
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllimport)
#endif

struct MATH_API Vec3 {  
    double x, y, z;

    Vec3(double x = 0.0, double y = 0.0, double z = 0.0);

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(double scalar) const;

    double length() const;
    void normalize();
};

MATH_API Vec3 operator*(double scalar, const Vec3& v);
MATH_API double dot(const Vec3& a, const Vec3& b);
MATH_API Vec3 cross(const Vec3& a, const Vec3& b);
MATH_API std::ostream& operator<<(std::ostream& os, const Vec3& v);