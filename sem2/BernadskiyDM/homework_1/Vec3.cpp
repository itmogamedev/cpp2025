#include "Vec3.h"
#include <cmath>
#include <ostream>

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}

Vec3::Vec3(double x_coord, double y_coord, double z_coord) : x(x_coord), y(y_coord), z(z_coord) {}

double Vec3::length() const {
  return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalized() const {
  double len = length();
  if (len == 0.0) {
    return Vec3(0.0, 0.0, 0.0);
  }
  return Vec3(x / len, y / len, z / len);
}

void Vec3::normalize() {
  double len = length();
  if (len == 0.0) {
    return;
  }
  x /= len;
  y /= len;       
  z /= len;
}

Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(double scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

double Vec3::dot(const Vec3& a, const Vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Vec3::cross(const Vec3& a, const Vec3& b) {
  return Vec3(
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x
  );
}

Vec3 operator*(double scalar, const Vec3& v) {
  return Vec3(scalar * v.x, scalar * v.y, scalar * v.z);
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}

