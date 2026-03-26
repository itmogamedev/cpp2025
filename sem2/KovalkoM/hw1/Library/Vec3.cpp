#include "Vec3.h"

namespace MathLib {
Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

Vec3::Vec3(float xValue, float yValue, float zValue)
    : x(xValue), y(yValue), z(zValue) {}

float Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

float Vec3::lengthSquared() const { return x * x + y * y + z * z; }

void Vec3::normalize() {
  const float len = length();
  if (len > 0.0f) {
    const float invLen = 1.0f / len;
    x *= invLen;
    y *= invLen;
    z *= invLen;
  }
}

Vec3 Vec3::normalized() const {
  const float len = length();
  if (len > 0.0f) {
    const float invLen = 1.0f / len;
    return Vec3(x * invLen, y * invLen, z * invLen);
  }
  return Vec3();
}

Vec3 operator+(const Vec3& a, const Vec3& b) {
  return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
  return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator*(const Vec3& v, float scalar) {
  return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

Vec3 operator*(float scalar, const Vec3& v) {
  return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

float dot(const Vec3& a, const Vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 cross(const Vec3& a, const Vec3& b) {
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
  return os;
}
}  // namespace MathLib
