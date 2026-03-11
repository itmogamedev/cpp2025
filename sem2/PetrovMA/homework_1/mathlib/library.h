#ifndef MATHLIB_LIBRARY_H
#define MATHLIB_LIBRARY_H
#include <iosfwd>

struct Vec3 {
    double x, y, z;
    double length();
    Vec3 normalize();

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    double operator*(const Vec3& other) const;
};
Vec3 vecSum(const Vec3& a, const Vec3& b);
Vec3 vecScalar(float fac, const Vec3& v);
double dot(const Vec3& a, const Vec3& b);
Vec3 cross(const Vec3& a, const Vec3& b);

std::ostream& operator<<(std::ostream& os, const Vec3& v);

#endif // MATHLIB_LIBRARY_H