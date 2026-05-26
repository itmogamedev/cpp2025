#ifndef VEC3_LIBRARY_VEC3_H_
#define VEC3_LIBRARY_VEC3_H_

#include <ostream>

#define VEC3_API

struct VEC3_API Vec3 {
    double x;
    double y;
    double z;

    Vec3();
    Vec3(double x_value, double y_value, double z_value);

    double length() const;
    Vec3 normalized() const;
};

VEC3_API Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
VEC3_API Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
VEC3_API Vec3 operator*(const Vec3& vec, double scalar);
VEC3_API Vec3 operator*(double scalar, const Vec3& vec);

VEC3_API double dot(const Vec3& lhs, const Vec3& rhs);
VEC3_API Vec3 cross(const Vec3& lhs, const Vec3& rhs);
VEC3_API std::ostream& operator<<(std::ostream& out, const Vec3& vec);

#endif  // VEC3_LIBRARY_VEC3_H_