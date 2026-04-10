#include "pch.h"

#define MATHVEC3_EXPORTS

#include <cmath>

#include "Vec3.h"

Vec3::Vec3() : x_coord(0.0f), y_coord(0.0f), z_coord(0.0f) {}
Vec3::Vec3(float x, float y, float z) : x_coord(x), y_coord(y), z_coord(z) {}

Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x_coord + other.x_coord, y_coord + other.y_coord,
              z_coord + other.z_coord);
}

Vec3 Vec3::operator-(const Vec3& other) const {
  return Vec3(x_coord - other.x_coord, y_coord - other.y_coord,
              z_coord - other.z_coord);
}

Vec3 Vec3::operator*(float scalar) const {
  return Vec3(x_coord * scalar, y_coord * scalar, z_coord * scalar);
}

MATHVEC3_API Vec3 operator*(float scalar, const Vec3& vec) {
  return Vec3(vec.x_coord * scalar, vec.y_coord * scalar, vec.z_coord * scalar);
}

float Vec3::skProduct(const Vec3& other) const {
  return x_coord * other.x_coord + y_coord * other.y_coord +
         z_coord * other.z_coord;
}

Vec3 Vec3::vcProduct(const Vec3& other) const {
  return Vec3(y_coord * other.z_coord - z_coord * other.y_coord,
              z_coord * other.x_coord - x_coord * other.z_coord,
              x_coord * other.y_coord - y_coord * other.x_coord);
}

float Vec3::length() const {
  return std::sqrt(x_coord * x_coord + y_coord * y_coord + z_coord * z_coord);
}

Vec3 Vec3::normalize() const {
  float len = length();

  if (len == 0.0f) {
    return Vec3();
  }
  return Vec3(x_coord / len, y_coord / len, z_coord / len);
}

MATHVEC3_API std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
  os << "(" << vec.x_coord << ", " << vec.y_coord << ", " << vec.z_coord << ")";
  return os;
}
