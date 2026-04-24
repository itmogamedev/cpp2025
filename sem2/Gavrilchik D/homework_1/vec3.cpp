#include "vec3.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}

Vec3::Vec3(double x_value, double y_value, double z_value)
    : x(x_value), y(y_value), z(z_value) {}

double Vec3::length() const {
  return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalized() const {
  double vec_length = length();
  if (vec_length == 0.0) {
    throw std::runtime_error("Cannot normalize zero vector.");
  }

  return Vec3(x / vec_length, y / vec_length, z / vec_length);
}

Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
  return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
  return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vec3 operator*(const Vec3& vec, double scalar) {
  return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

Vec3 operator*(double scalar, const Vec3& vec) {
  return vec * scalar;
}

double dot(const Vec3& lhs, const Vec3& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vec3 cross(const Vec3& lhs, const Vec3& rhs) {
  return Vec3(
      lhs.y * rhs.z - lhs.z * rhs.y,
      lhs.z * rhs.x - lhs.x * rhs.z,
      lhs.x * rhs.y - lhs.y * rhs.x);
}

std::ostream& operator<<(std::ostream& out, const Vec3& vec) {
  out << "Vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return out;
}