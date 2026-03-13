#ifndef MATHLIB_VEC3_H
#define MATHLIB_VEC3_H

#include <iostream>

#ifdef MATHLIB1_EXPORTS
#define MATHLIB_API __declspec(dllexport)
#else
#define MATHLIB_API __declspec(dllimport)
#endif

namespace mathlib {

    class MATHLIB_API Vec3 {
    public:
        Vec3();
        Vec3(double x, double y, double z);

        double dot(const Vec3& other) const;
        Vec3 cross(const Vec3& other) const;
        double length() const;
        Vec3 normalize() const;

        friend MATHLIB_API Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
        friend MATHLIB_API Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
        friend MATHLIB_API Vec3 operator*(const Vec3& vec, double scalar);
        friend MATHLIB_API Vec3 operator*(double scalar, const Vec3& vec);
        friend MATHLIB_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);

    private:
        double x_;
        double y_;
        double z_;
    };

} // namespace mathlib

#endif