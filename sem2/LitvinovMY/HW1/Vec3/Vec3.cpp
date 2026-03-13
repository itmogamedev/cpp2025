#include "pch.h" 
#include "Vec3.h"
#include <cmath>

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator*(double scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::operator/(double scalar) const {
  return Vec3(x / scalar, y / scalar, z / scalar);
}

Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

double Vec3::dot(const Vec3& other) const {
  return (x * other.x + y * other.y + z * other.z);
}

double Vec3::operator*(const Vec3& other) const {
  return dot(other);
}

Vec3 Vec3::cross(const Vec3& other) const {
  double xn = y * other.z - z * other.y;
  double yn = z * other.x - x * other.z;
  double zn = x * other.y - y * other.x;
  return Vec3(xn, yn, zn);
}

Vec3 Vec3::operator^(const Vec3& other) const {
  return cross(other);
}

double Vec3::length() const {
  double sum = x * x + y * y + z * z;
  double len = std::sqrt(sum);
  return len;
};

Vec3 Vec3::normalized() const {
  double len = length();
  if (len) {
    return *this / len;
  }
  else {
    return Vec3();
  }
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << '(' << v.x << ' ' << v.y << ' ' << v.z << ')';
  return os;
}
