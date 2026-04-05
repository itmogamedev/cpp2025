#include "pch.h"
#include "math_vector.h"

#include <cmath>


Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3::Vec3(const Vec3& other) : x(other.x), y(other.y), z(other.z) {}

Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(double scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
  os << "Vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return os;
}

Vec3 operator*(double scalar, const Vec3& vec) {
  return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

Vec3 Add(const Vec3& a, const Vec3& b) { return a + b; }

Vec3 Subtract(const Vec3& a, const Vec3& b) { return a - b; }

Vec3 Multiply(const Vec3& vec, double scalar) { return vec * scalar; }

double DotProduct(const Vec3& a, const Vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 CrossProduct(const Vec3& a, const Vec3& b) {
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

double Length(const Vec3& vec) {
  return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

Vec3 Normalize(const Vec3& vec) {
  double len = Length(vec);
  if (len > 0) {
    return Vec3(vec.x / len, vec.y / len, vec.z / len);
  }
  return Vec3(0, 0, 0);
}
