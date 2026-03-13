#include "pch.h"

#include "Vec3Lib.h"

Vec3::Vec3() {
  x = 0;
  y = 0;
  z = 0;
}
Vec3::Vec3(float _x, float _y, float _z) {
  x = _x;
  y = _y;
  z = _z;
}
Vec3::Vec3(const Vec3& other) {
  x = other.x;
  y = other.y;
  z = other.z;
}
Vec3& Vec3::operator=(const Vec3& other) {
  if (this != &other) {
    x = other.x;
    y = other.y;
    z = other.z;
  }
  return *this;
}
Vec3 operator+(const Vec3& a, const Vec3& b) {
  return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}
Vec3 operator-(const Vec3& a, const Vec3& b) {
  return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}
Vec3 operator*(const Vec3& a, float value) {
  return Vec3(a.x * value, a.y * value, a.z * value);
}
Vec3 operator*(float value, const Vec3& a) {
  return Vec3(a.x * value, a.y * value, a.z * value);
}
std::ostream& operator<<(std::ostream& os, const Vec3& a) {
  os << "(" << a.x << ", " << a.y << ", " << a.z << ")";
  return os;
}
float Vec3::length() const { return sqrt(x * x + y * y + z * z); }
void Vec3::normalize() {
  float len = length();
  x = x / len;
  y = y / len;
  z = z / len;
}
Vec3 Vec3::normalized() const {
  float len = length();
  return Vec3(x / len, y / len, z / len);
}
float Vec3::dot(Vec3& other) const {
  return x * other.x + y * other.y + z * other.z;
}
Vec3 Vec3::cross(Vec3& other) const {
  return Vec3(y * other.z - z * other.y, z * other.x - x * other.z,
              x * other.y - y * other.x);
}
