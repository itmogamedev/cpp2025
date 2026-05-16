#include "vec3.h"

#include <cmath>

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(double scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 operator*(double scalar, const Vec3& vec) { return vec * scalar; }

double Vec3::dot(const Vec3& other) const {
  return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3& other) const {
  return Vec3(y * other.z - z * other.y, z * other.x - x * other.z,
              x * other.y - y * other.x);
}

double Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

void Vec3::normalize() {
  double len = length();
  if (len > 0) {
    x /= len;
    y /= len;
    z /= len;
  }
}

Vec3 Vec3::normalized() const {
  double len = length();
  if (len > 0) {
    return Vec3(x / len, y / len, z / len);
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
  os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return os;
}
