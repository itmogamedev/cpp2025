#include "pch.h"
#include "MathLibrary.h"
#include <cmath>


Vec::Vec(float x, float y, float z) : x(x), y(y), z(z) {}

//+
Vec Vec::operator+(const Vec& other) const {
  return Vec(x + other.x, y + other.y, z + other.z);
}

//-
Vec Vec::operator-(const Vec& other) const {
  return Vec(x - other.x, y - other.y, z - other.z);
}

// na number
Vec Vec::operator*(float s) const {
  return Vec(x * s, y * s, z * s);
}
//dlina
float Vec::length() const {
  return std::sqrt(x * x + y * y + z * z);
}
// norma
Vec Vec::normalize() const {
  float len = std::sqrt(x * x + y * y + z * z);
  if (len > 0) {
    float newX = x / len;
    float newY = y / len;
    float newZ = z / len;
    return Vec(newX, newY, newZ);
  }
  return Vec(0, 0, 0);
}

// scalar proiz
float Vec::operator*(const Vec& other) const {
  return (x * other.x + y * other.y + z * other.z);
}
//vec proiz
Vec Vec::cross(const Vec& other) const {
  float newX = (y * other.z) - (z * other.y);
  float newY = (z * other.x) - (x * other.z);
  float newZ = (x * other.y) - (y * other.x);

  return Vec(newX, newY, newZ);
}
// vivod
std::ostream& operator<<(std::ostream& vivod, const Vec& v) {
  vivod << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return vivod;
}