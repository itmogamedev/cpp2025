#ifndef VEC3_H
#define VEC3_H

#include <iostream>

#include "math_lib_export.h"

struct MATHLIB_API Vec3 {
  double x;
  double y;
  double z;

  Vec3();
  Vec3(double x, double y, double z);

  double length() const;
  Vec3 normalize() const;

  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(double scalar) const;

  double dot(const Vec3& other) const;
  Vec3 cross(const Vec3& other) const;
};

MATHLIB_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);

#endif
