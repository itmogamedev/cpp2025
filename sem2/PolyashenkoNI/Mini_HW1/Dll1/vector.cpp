#include "pch.h"
#include "vector.h"

#include <cmath>

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3 operator+(const Vec3& a, const Vec3& b) {
  return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
  return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator*(const Vec3& v, float scal) {
  return Vec3(v.x * scal, v.y * scal, v.z * scal);
}

Vec3 operator*(float scal, const Vec3& v) { return v * scal; }

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}

float Vec3::lenght() const { return std::sqrt(x * x + y * y + z * z); }

void Vec3::normalizator() {
  float len = lenght();
  if (len > 0) {
    x /= len;
    y /= len;
    z /= len;
  }
}

Vec3 Vec3::normalezd() const {
  Vec3 result = *this;
  result.normalizator();
  return result;
}

float Vec3::scalyarMulti(const Vec3& second) const {
  return x * second.x + y * second.y + z * second.z;
}

Vec3 Vec3::veñMulti(const Vec3& second) {
  return Vec3(y * second.z - z * second.y, z * second.x - x * second.z,
              x * second.y - y * second.x);
}
