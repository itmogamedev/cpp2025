#include "pch.h"

#include "Vec3.h"

#include <cmath>



Vec3 Vec3::operator+(const Vec3& second) const {
  return Vec3(x + second.x, y + second.y, z + second.z);
}

Vec3 Vec3::operator-(const Vec3& second) const {
  return Vec3(x - second.x, y - second.y, z - second.z);
}

Vec3 Vec3::operator*(float scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

float Vec3::dot(const Vec3& second) const {
  return (x * second.x) + (y * second.y) + (z * second.z);
}

Vec3 Vec3::cross(const Vec3& second) const {
  return Vec3(y * second.z - second.y * z, second.x * z - x * second.z,
              x * second.y - second.x * y);
}

float Vec3::length() const { return sqrt(x * x + y * y + z * z); }

Vec3 Vec3::normalized() const {
  float len = length();
  return Vec3(x / len, y / len, z / len);
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}
