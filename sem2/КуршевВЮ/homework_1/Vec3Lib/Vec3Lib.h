#pragma once

#ifdef VEC3LIB_EXPORTS
#define VEC3LIB_API __declspec(dllexport)
#else
#define VEC3LIB_API __declspec(dllimport)
#endif

#include <iostream>

struct VEC3LIB_API Vec3 {
    double x, y, z;

    Vec3(double x = 0, double y = 0, double z = 0);

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(double scalar) const;
};

VEC3LIB_API std::ostream& operator<<(std::ostream& os, const Vec3& vector);

VEC3LIB_API Vec3 add(const Vec3& vector_a, const Vec3& vector_b);
VEC3LIB_API Vec3 subtract(const Vec3& vector_a, const Vec3& vector_b);
VEC3LIB_API Vec3 multiply(const Vec3& vector, double scalar);
VEC3LIB_API double scalMult(const Vec3& vector_a, const Vec3& vector_b);
VEC3LIB_API Vec3 vectMult(const Vec3& vector_a, const Vec3& vector_b);
VEC3LIB_API double length(const Vec3& vector);
VEC3LIB_API Vec3 normalize(const Vec3& vector);
VEC3LIB_API Vec3 operator*(double scalar, const Vec3& vector);
