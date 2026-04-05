#include "MathLibrary.h"

#include <cmath>

#include "pch.h"

Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3 add(const Vec3& a, const Vec3& b) {
  return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 subtract(const Vec3& a, const Vec3& b) {
  return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 multiplyByScalar(const Vec3& v, float scalar) {
  return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

float dotProduct(const Vec3& a, const Vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 crossProduct(const Vec3& a, const Vec3& b) {
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

float length(const Vec3& v) {
  return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 normalize(const Vec3& v) {
  float len = length(v);
  if (len == 0.0f) {
    return Vec3(0.0f, 0.0f, 0.0f);
  }
  return Vec3(v.x / len, v.y / len, v.z / len);
}

Vec3 operator+(const Vec3& a, const Vec3& b) { return add(a, b); }

Vec3 operator-(const Vec3& a, const Vec3& b) { return subtract(a, b); }

Vec3 operator*(const Vec3& v, float scalar) {
  return multiplyByScalar(v, scalar);
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}
