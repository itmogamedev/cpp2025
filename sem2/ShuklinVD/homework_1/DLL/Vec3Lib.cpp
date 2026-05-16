#include "pch.h" 
#include "Vec3Lib.h"
#ifndef VEC3LIB_EXPORTS
#define VEC3LIB_EXPORTS
#endif

Vec3::Vec3(float n_x, float n_y, float n_z) : x(n_x), y(n_y), z(n_z) {}

Vec3 Vec3::operator+(const Vec3& vec) const {
  return Vec3(x + vec.x, y + vec.y, z + vec.z);
}

Vec3 Vec3::operator-(const Vec3& vec) const {
  return Vec3(x - vec.x, y - vec.y, z - vec.z);
}

float Vec3::operator*(const Vec3& vec) const {
  return x * vec.x + y * vec.y + z * vec.z;
}

Vec3 Vec3::operator*(const int& scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

float Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

Vec3 Vec3::normalize() const {
  float len = length();
  if (len == 0) {
    std::cout << "length of vector 0 !!!";
    return Vec3(0, 0, 0);
  }
  return Vec3(x / len, y / len, z / len);
}

Vec3 crossProduct(const Vec3& vec_1, const Vec3& vec_2) {
  return Vec3(vec_1.y * vec_2.z - vec_1.z * vec_2.y,
              vec_1.z * vec_2.x - vec_1.x * vec_2.z,
              vec_1.x * vec_2.y - vec_1.y * vec_2.x);
}

