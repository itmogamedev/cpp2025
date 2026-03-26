#pragma once

#ifdef VEC3LIB_EXPORTS
#define VEC3LIB_API __declspec(dllexport)
#else
#define VEC3LIB_API __declspec(dllimport)
#endif
#include <iostream>
struct Vec3 {
  float x, y, z;

  VEC3LIB_API Vec3(float n_x, float n_y, float n_z);
  VEC3LIB_API Vec3 operator+(const Vec3& vec) const;
  VEC3LIB_API Vec3 operator-(const Vec3& vec) const;
  VEC3LIB_API float operator*(const Vec3& vec) const;
  VEC3LIB_API Vec3 operator*(const int& scalar) const;
  VEC3LIB_API float length() const;
  VEC3LIB_API Vec3 normalize() const;
  friend std::ostream& operator<<(std::ostream& os, const Vec3& v);
};

VEC3LIB_API Vec3 crossProduct(const Vec3& vec_1, const Vec3& vec_2);
inline std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}
