#pragma once

#include <cmath>
#include <ostream>

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIB_API __declspec(dllexport)
#else
#define MATHLIB_API __declspec(dllimport)
#endif

namespace MathLib {
struct MATHLIB_API Vec3 {
  float x;
  float y;
  float z;

  Vec3();
  Vec3(float x, float y, float z);

  float length() const;
  float lengthSquared() const;

  void normalize();
  Vec3 normalized() const;
};

MATHLIB_API Vec3 operator+(const Vec3& a, const Vec3& b);
MATHLIB_API Vec3 operator-(const Vec3& a, const Vec3& b);

MATHLIB_API Vec3 operator*(const Vec3& v, float scalar);
MATHLIB_API Vec3 operator*(float scalar, const Vec3& v);

MATHLIB_API float dot(const Vec3& a, const Vec3& b);
MATHLIB_API Vec3 cross(const Vec3& a, const Vec3& b);

MATHLIB_API std::ostream& operator<<(std::ostream& os, const Vec3& v);
}  // namespace MathLib
