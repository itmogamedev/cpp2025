#include "vec3.h"

#include <cmath>

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

double Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

void Vec3::normalize() {
  double len = length();
  if (len > 0.0) {
    x /= len;
    y /= len;
    z /= len;
  }
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

Vec3 operator*(double scalar, const Vec3& v) { return v * scalar; }

double dot(const Vec3& a, const Vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 cross(const Vec3& a, const Vec3& b) {
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}
