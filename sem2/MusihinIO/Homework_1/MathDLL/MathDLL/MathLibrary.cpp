// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "MathLibrary.h"

#include <cmath>
#include <limits>

#include "pch.h"

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3 Vec3::add(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::subtract(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::multiply(double scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

double Vec3::dot(const Vec3& other) const {
  return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3& other) const {
  return Vec3(y * other.z - z * other.y, z * other.x - x * other.z,
              x * other.y - y * other.x);
}

double Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

Vec3 Vec3::normalize() const {
  double len = length();
  if (len < std::numeric_limits<double>::epsilon()) {
    return Vec3(0.0, 0.0, 0.0);
  }
  return Vec3(x / len, y / len, z / len);
}

Vec3 operator+(const Vec3& lhs, const Vec3& rhs) { return lhs.add(rhs); }

Vec3 operator-(const Vec3& lhs, const Vec3& rhs) { return lhs.subtract(rhs); }

Vec3 operator*(const Vec3& vec, double scalar) { return vec.multiply(scalar); }

Vec3 operator*(double scalar, const Vec3& vec) { return vec.multiply(scalar); }

std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
  os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return os;
}
