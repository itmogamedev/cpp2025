#include "MathLibrary.h"

#include <cmath>
#include <iostream>

Vec3::Vec3() {
  x_coord = 0;
  y_coord = 0;
  z_coord = 0;
}

Vec3::Vec3(double x, double y, double z) {
  x_coord = x;
  y_coord = y;
  z_coord = z;
}

Vec3::Vec3(const Vec3& other) {
  x_coord = other.x_coord;
  y_coord = other.y_coord;
  z_coord = other.z_coord;
}

Vec3 Vec3::operator+(const Vec3& other) const {
  Vec3 result;
  result.x_coord = x_coord + other.x_coord;
  result.y_coord = y_coord + other.y_coord;
  result.z_coord = z_coord + other.z_coord;
  return result;
}

Vec3 Vec3::operator-(const Vec3& other) const {
  Vec3 result;
  result.x_coord = x_coord - other.x_coord;
  result.y_coord = y_coord - other.y_coord;
  result.z_coord = z_coord - other.z_coord;
  return result;
}

Vec3 Vec3::operator*(double scalar) const {
  Vec3 result;
  result.x_coord = x_coord * scalar;
  result.y_coord = y_coord * scalar;
  result.z_coord = z_coord * scalar;
  return result;
}

MATHLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
  os << "(" << vec.x_coord << ", " << vec.y_coord << ", " << vec.z_coord << ")";
  return os;
}

MATHLIBRARY_API Vec3 operator*(double scalar, const Vec3& vec) {
  Vec3 result;
  result.x_coord = vec.x_coord * scalar;
  result.y_coord = vec.y_coord * scalar;
  result.z_coord = vec.z_coord * scalar;
  return result;
}

Vec3 addVectors(const Vec3& a, const Vec3& b) {
  Vec3 result;
  result.x_coord = a.x_coord + b.x_coord;
  result.y_coord = a.y_coord + b.y_coord;
  result.z_coord = a.z_coord + b.z_coord;
  return result;
}

Vec3 subtractVectors(const Vec3& a, const Vec3& b) {
  Vec3 result;
  result.x_coord = a.x_coord - b.x_coord;
  result.y_coord = a.y_coord - b.y_coord;
  result.z_coord = a.z_coord - b.z_coord;
  return result;
}

Vec3 multiplyByScalar(const Vec3& vec, double scalar) {
  Vec3 result;
  result.x_coord = vec.x_coord * scalar;
  result.y_coord = vec.y_coord * scalar;
  result.z_coord = vec.z_coord * scalar;
  return result;
}

double dotProduct(const Vec3& a, const Vec3& b) {
  return a.x_coord * b.x_coord + a.y_coord * b.y_coord + a.z_coord * b.z_coord;
}

Vec3 crossProduct(const Vec3& a, const Vec3& b) {
  Vec3 result;
  result.x_coord = a.y_coord * b.z_coord - a.z_coord * b.y_coord;
  result.y_coord = a.z_coord * b.x_coord - a.x_coord * b.z_coord;
  result.z_coord = a.x_coord * b.y_coord - a.y_coord * b.x_coord;
  return result;
}

double vectorLength(const Vec3& vec) {
  return std::sqrt(vec.x_coord * vec.x_coord + vec.y_coord * vec.y_coord +
                   vec.z_coord * vec.z_coord);
}

Vec3 normalizeVector(const Vec3& vec) {
  double len = vectorLength(vec);
  if (len > 0) {
    Vec3 result;
    result.x_coord = vec.x_coord / len;
    result.y_coord = vec.y_coord / len;
    result.z_coord = vec.z_coord / len;
    return result;
  }
  return Vec3();
}
