#include "Vec3.h"

#include <cmath>

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}

Vec3::Vec3(double x_value, double y_value, double z_value)
    : x(x_value), y(y_value), z(z_value) {}

Vec3 Vec3::add(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::subtract(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::multiplyByScalar(double scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

double Vec3::scalarMultiply(const Vec3& other) const {
  return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::vectorMultiply(const Vec3& other) const {
  return Vec3(y * other.z - z * other.y, z * other.x - x * other.z,
              x * other.y - y * other.x);
}

double Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

Vec3 Vec3::normalize() const {
  double vec_length = length();

  if (vec_length == 0.0) {
    return Vec3(0.0, 0.0, 0.0);
  }

  return Vec3(x / vec_length, y / vec_length, z / vec_length);
}

Vec3 Vec3::operator+(const Vec3& other) const { return add(other); }

Vec3 Vec3::operator-(const Vec3& other) const { return subtract(other); }

Vec3 Vec3::operator*(double scalar) const { return multiplyByScalar(scalar); }

std::ostream& operator<<(std::ostream& out, const Vec3& vec) {
  out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return out;
}
