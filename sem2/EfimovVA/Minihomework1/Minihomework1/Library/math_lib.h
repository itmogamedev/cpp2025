#ifndef MATH_LIB_H
#define MATH_LIB_H

#include <iostream>

#ifdef MATHLIB_EXPORTS
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllimport)
#endif

struct MATH_API Vec3 {
  float x;
  float y;
  float z;

  Vec3();

  Vec3(float init_x, float init_y, float init_z);

  float length() const;
  void normalize();

  float dotProduct(const Vec3& other) const;
  Vec3 crossProduct(const Vec3& other) const;

  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;

  Vec3 operator*(float scalar) const;
};

MATH_API std::ostream& operator<<(std::ostream& os, const Vec3& vector);

#endif