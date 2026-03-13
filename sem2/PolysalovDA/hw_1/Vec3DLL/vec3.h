#pragma once
#ifdef VEC3DLL_EXPORTS
#define VEC3_API __declspec(dllexport)
#else
#define VEC3_API __declspec(dllimport)
#endif

#include <cmath>  // std::sqrt
#include <iostream>

struct VEC3_API Vec3 {
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;

  Vec3() = default;
  Vec3(float x, float y, float z);

  float length() const;
  void normalize();
  Vec3 normalized() const;

  float dot(const Vec3& other) const;
  Vec3 cross(const Vec3& other) const;
};

// свободные функции — без изменений, здесь порядок правильный
VEC3_API Vec3 operator+(const Vec3& a, const Vec3& b);
VEC3_API Vec3 operator-(const Vec3& a, const Vec3& b);
VEC3_API Vec3 operator*(const Vec3& v, float scalar);
VEC3_API Vec3 operator*(float scalar, const Vec3& v);

VEC3_API std::ostream& operator<<(std::ostream& os, const Vec3& v);
