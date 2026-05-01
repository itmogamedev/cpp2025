#define MATHLIB_EXPORTS

#include "math_lib.h"

#include <cmath>

const float ZERO_FLOAT = 0.0f;

Vec3::Vec3() {
  x = ZERO_FLOAT;
  y = ZERO_FLOAT;
  z = ZERO_FLOAT;
}

Vec3::Vec3(float init_x, float init_y, float init_z) {
  x = init_x;
  y = init_y;
  z = init_z;
}

float Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

void Vec3::normalize() {
  float vec_length = length();
  if (vec_length > ZERO_FLOAT) {
    x = x / vec_length;
    y = y / vec_length;
    z = z / vec_length;
  }
}

float Vec3::dotProduct(const Vec3& other) const {
  return (x * other.x) + (y * other.y) + (z * other.z);
}

Vec3 Vec3::crossProduct(const Vec3& other) const {
  float new_x = (y * other.z) - (z * other.y);
  float new_y = (z * other.x) - (x * other.z);
  float new_z = (x * other.y) - (y * other.x);
  return Vec3(new_x, new_y, new_z);
}

Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(float scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

std::ostream& operator<<(std::ostream& os, const Vec3& vector) {
  os << "[" << vector.x << ", " << vector.y << ", " << vector.z << "]";
  return os;
}