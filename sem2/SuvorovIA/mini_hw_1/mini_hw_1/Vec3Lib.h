#pragma once

#ifdef VEC3LIBRARY_EXPORTS
#define VEC3LIB_API __declspec(dllexport)
#else
#define VEC3LIB_API __declspec(dllimport)
#endif

#include <iostream>

struct VEC3LIB_API Vec3 {
  float x;
  float y;
  float z;

  Vec3();
  Vec3(float x, float y, float z);
  Vec3(const Vec3& other);
  Vec3& operator=(const Vec3& other);

  float length() const;
  void normalize();
  Vec3 normalized() const;
  float dot(Vec3& other) const;
  Vec3 cross(Vec3& other) const;
};

inline std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}

VEC3LIB_API Vec3 operator+(const Vec3& a, const Vec3& b);
VEC3LIB_API Vec3 operator-(const Vec3& a, const Vec3& b);
VEC3LIB_API Vec3 operator*(const Vec3& a, float value);
VEC3LIB_API Vec3 operator*(float value, const Vec3& a);
