#include "vectorlib.h"

#include <cmath>

#include "pch.h"

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(Vec3 v) { return Vec3(x + v.x, y + v.y, z + v.z); }

Vec3 Vec3::operator-(Vec3 v) { return Vec3(x - v.x, y - v.y, z - v.z); }

Vec3 Vec3::operator*(float n) { return Vec3(x * n, y * n, z * n); }

float Vec3::scalarMulti(Vec3 v) { return x * v.x + y * v.y + z * v.z; }

Vec3 Vec3::vectorMulti(Vec3 v) {
  return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

float Vec3::vectorLength() { return std::sqrt(x * x + y * y + z * z); }

Vec3 Vec3::normal() {
  double len = vectorLength();
  if (len > 0.0) {
    return Vec3(x / len, y / len, z / len);
  }
  return Vec3(0, 0, 0);
}

std::ostream& operator<<(std::ostream& os, Vec3& v) {
  os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}
