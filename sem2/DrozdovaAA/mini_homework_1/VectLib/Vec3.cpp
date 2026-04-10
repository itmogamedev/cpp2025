#include "pch.h"

// Комментарий для тупого гугл стайла, который сортирует по алфавиту!!
#include <cmath>
#include <iostream>

#include "Vec3.h"

// перегрузка операторов
Vec3 Vec3::operator+(const Vec3& other) const {
  return {x + other.x, y + other.y, z + other.z};
}

Vec3 Vec3::operator-(const Vec3& other) const {
  return {x - other.x, y - other.y, z - other.z};
}

Vec3 Vec3::operator*(double scalar) const {
  return {x * scalar, y * scalar, z * scalar};
}

Vec3 Vec3::operator/(double scalar) const {
  return {x / scalar, y / scalar, z / scalar};
}

// задание 2
Vec3 plusVectors(const Vec3& v1, const Vec3& v2) { return v1 + v2; }

Vec3 minusVectors(const Vec3& v1, const Vec3& v2) { return v1 - v2; }

double dotProduct(const Vec3& v1, const Vec3& v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 vectorProduct(const Vec3& v1, const Vec3& v2) {
  return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
          v1.x * v2.y - v1.y * v2.x};
}

double vectorLength(const Vec3& v) {
  return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 vectorNormalize(const Vec3& v) {
  double len = vectorLength(v);
  if (len > 0) {
    return v / len;
  }
  return {0, 0, 0};  // Если вектор нулевой
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}
