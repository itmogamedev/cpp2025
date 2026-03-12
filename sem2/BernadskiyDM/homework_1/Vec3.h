#pragma once
#include <iosfwd>

#ifdef _WIN32
  #ifdef VEC3LIB_EXPORTS
    #define VEC3_API __declspec(dllexport)
  #else
    #define VEC3_API __declspec(dllimport)
  #endif
#else
  #define VEC3_API
#endif

class VEC3_API Vec3 {
public:
    double x;
    double y;
    double z;

    Vec3();
    Vec3(double x, double y, double z);

    double length() const;
    Vec3 normalized() const;
    void normalize();

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;

    Vec3 operator*(double scalar) const;

    static double dot(const Vec3& a, const Vec3& b);

    static Vec3 cross(const Vec3& a, const Vec3& b);
};

VEC3_API Vec3 operator*(double scalar, const Vec3& v);

VEC3_API std::ostream& operator<<(std::ostream& os, const Vec3& v);

