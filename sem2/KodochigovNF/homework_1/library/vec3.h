#pragma once

#include <iostream>

#ifdef VEC3LIB_EXPORTS
#define VEC3_API __declspec(dllexport)
#else
#define VEC3_API __declspec(dllimport)
#endif

struct VEC3_API Vec3 {
  double x, y, z;

  Vec3(double x = 0, double y = 0, double z = 0);

  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(double scalar) const;
  friend VEC3_API Vec3 operator*(double scalar, const Vec3& vec);

  double dot(const Vec3& other) const;

  Vec3 cross(const Vec3& other) const;

  double length() const;

  void normalize();

  Vec3 normalized() const;

  friend VEC3_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);
};
