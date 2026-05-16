#include "Libra.h"

#include <cmath>

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3& other) const {
  return {x + other.x, y + other.y, z + other.z};
}
Vec3 Vec3::operator-(const Vec3& other) const {
  return {x - other.x, y - other.y, z - other.z};
}
float Vec3::operator*(const Vec3& other) const {
  return (x * other.x) + (y * other.y) + (z * other.z);
}
Vec3 Vec3::operator*(float scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::cross(const Vec3& other) const {
  return {y * other.z - z * other.y, z * other.x - x * other.z,
          x * other.y - y * other.x};
}

float Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

Vec3 Vec3::normalize() const {
  float len = length();
  if (len > 0) return *this * (1.0f / len);
  return *this;
}

std::ostream& operator<<(std::ostream& output, const Vec3& v) {
  output << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return output;
}
