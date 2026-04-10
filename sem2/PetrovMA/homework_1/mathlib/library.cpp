#include "library.h"

#include <cmath>
#include <iostream>

namespace mathlib {

  Vec3 vecSum(const Vec3& a, const Vec3& b) {
    return Vec3{a.x + b.x, a.y + b.y, a.z + b.z};
  }

  Vec3 vecScalar(float fac, const Vec3& v) {
    return Vec3{fac * v.x, fac * v.y, fac * v.z};
  }

  double dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }

  Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3{
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
  }

  double Vec3::length() const {
    return sqrt(x * x + y * y + z * z);
  }

  Vec3 Vec3::normalize() const {
    auto len = length();
    return Vec3{x / len, y / len, z / len};
  }

  Vec3 Vec3::operator+(const Vec3& other) const {
    return vecSum(*this, other);
  }

  Vec3 Vec3::operator-(const Vec3& other) const {
    return vecSum(*this, Vec3{-other.x, -other.y, -other.z});
  }

  double Vec3::operator*(const Vec3& other) const {
    return dot(*this, other);
  }

  std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
  }

}
