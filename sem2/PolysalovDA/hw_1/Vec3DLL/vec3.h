#pragma once
#ifdef VEC3DLL_EXPORTS
#define VEC3_API __declspec(dllexport)
#else
#define VEC3_API __declspec(dllimport)
#endif

#include <cmath>
#include <iostream>

struct VEC3_API Vec3 {
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;

  Vec3() = default;
  Vec3(float x, float y, float z);

  float length() const;
  void normalize();

  float scalarMultiply(const Vec3& other) const;
  Vec3 vectorMultiply(const Vec3& other) const;
};

VEC3_API Vec3 operator+(const Vec3& a, const Vec3& b);
VEC3_API Vec3 operator-(const Vec3& a, const Vec3& b);
VEC3_API Vec3 operator*(const Vec3& v, float scalar);
VEC3_API Vec3 operator*(float scalar, const Vec3& v);

VEC3_API std::ostream& operator<<(std::ostream& os, const Vec3& v);
