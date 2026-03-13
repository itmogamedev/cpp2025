#pragma once

#ifdef _WIN32
    #ifdef MATHLIB_EXPORTS
        #define MATHLIB_API __declspec(dllexport)
    #else
        #define MATHLIB_API __declspec(dllimport)
    #endif
#else
    #define MATHLIB_API
#endif

#include <iostream>

class MATHLIB_API Vec3 {
public:
    double x;
    double y;
    double z;

    Vec3();
    Vec3(double x, double y, double z);

    double length() const;
    void normalize();

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(double scalar) const;
};

MATHLIB_API Vec3 operator*(double scalar, const Vec3& v);
MATHLIB_API double dot(const Vec3& a, const Vec3& b);
MATHLIB_API Vec3 cross(const Vec3& a, const Vec3& b);
MATHLIB_API std::ostream& operator<<(std::ostream& os, const Vec3& v);