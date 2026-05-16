
#define MATHLIB_EXPORTS

#pragma once

#ifdef MATHLIB_EXPORTS
#include "pch.h"
#define MATHLIB_API __declspec(dllexport)
#else
#define MATHLIB_API __declspec(dllimport)
#endif

struct MATHLIB_API Vec3 {
  double x = 0, y = 0, z = 0;

  Vec3(double x, double y, double z);

  Vec3 operator+(Vec3& other) const;
  Vec3 operator-(Vec3& other) const;
  Vec3 operator*(Vec3& other) const;
  Vec3 operator*(double scale) const;
  Vec3 operator/(double scale) const;

  double getLenght() const;
  void normalize();

  friend std::ostream& operator<<(std::ostream& os, const Vec3& v);
};

MATHLIB_API Vec3 cross(const Vec3& first, const Vec3 second);

inline std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}
