
#include "MathLibrary.h"

#include <cmath>

#include "pch.h"

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

Vec3 Vec3::operator/(double scalar) const {
  if (std::fabs(scalar) < 1e-10) {
    return Vec3(0, 0, 0);  // Защита от деления на ноль
  }
  return Vec3(x / scalar, y / scalar, z / scalar);
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}

Vec3 add(const Vec3& a, const Vec3& b) { return a + b; }

Vec3 subtract(const Vec3& a, const Vec3& b) { return a - b; }

Vec3 multiply_scalar(const Vec3& v, double scalar) { return v * scalar; }

double dot_product(const Vec3& a, const Vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 cross_product(const Vec3& a, const Vec3& b) {
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

double vector_length(const Vec3& v) {
  return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 normalize_vector(const Vec3& v) {
  double len = vector_length(v);
  if (len < 1e-10) {
    return Vec3(0, 0, 0);  // Возвращаем нулевой вектор для нулевой длины
  }
  return v / len;
}
