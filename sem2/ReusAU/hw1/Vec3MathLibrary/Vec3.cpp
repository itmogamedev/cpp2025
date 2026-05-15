#include "Vec3.h"

#include <cmath>
#include <stdexcept>

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}

Vec3::Vec3(double x_value, double y_value, double z_value)
    : x(x_value), y(y_value), z(z_value) {}

double Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

Vec3 Vec3::normalize() const {
  double vector_length = length();

  if (vector_length == 0.0) {
    throw std::runtime_error("Cannot normalize zero vector.");
  }

  return Vec3(x / vector_length, y / vector_length, z / vector_length);
}

Vec3 operator+(const Vec3& left, const Vec3& right) {
  return Vec3(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vec3 operator-(const Vec3& left, const Vec3& right) {
  return Vec3(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vec3 operator*(const Vec3& vector, double scalar) {
  return Vec3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

std::ostream& operator<<(std::ostream& out, const Vec3& vector) {
  out << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
  return out;
}

double dotProduct(const Vec3& left, const Vec3& right) {
  return left.x * right.x + left.y * right.y + left.z * right.z;
}

Vec3 crossProduct(const Vec3& left, const Vec3& right) {
  return Vec3(left.y * right.z - left.z * right.y,
              left.z * right.x - left.x * right.z,
              left.x * right.y - left.y * right.x);
}
