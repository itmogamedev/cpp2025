#pragma once
#include <iostream>

#ifdef VEC3_EXPORTS
#define VEC3_API __declspec(dllexport)
#else
#define VEC3_API __declspec(dllimport)
#endif

struct VEC3_API Vec3 {
  double x;
  double y;
  double z;

  Vec3();
  Vec3(double x, double y, double z);

  double length() const;
  Vec3 normalize() const;
};

VEC3_API Vec3 cross(const Vec3& a, const Vec3& b);

VEC3_API Vec3 operator+(const Vec3& a, const Vec3& b);
VEC3_API Vec3 operator-(const Vec3& a, const Vec3& b);
VEC3_API Vec3 operator*(const Vec3& v, double s);
VEC3_API double operator*(const Vec3& a, const Vec3& b);
VEC3_API std::ostream& operator<<(std::ostream& os, const Vec3& v);
