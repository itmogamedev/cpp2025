#include <cmath>
#include <ostream>

#include "Vec3.h"

Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3::Vec3(double x, double y, double z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

double Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

Vec3 Vec3::normalize() const {
  double len = length();
  if (len == 0) return Vec3(0, 0, 0);
  return Vec3(x / len, y / len, z / len);
}

Vec3 cross(const Vec3& a, const Vec3& b) {
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

Vec3 operator+(const Vec3& a, const Vec3& b) {
  return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
  return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator*(const Vec3& v, double s) {
  return Vec3(v.x * s, v.y * s, v.z * s);
}

double operator*(const Vec3& a, const Vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
