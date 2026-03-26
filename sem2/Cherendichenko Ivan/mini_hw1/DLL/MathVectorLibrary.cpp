
#include "pch.h"

// Затем ваш заголовок
#include "MathVectorLibrary.h"

// Реализация методов структуры
double Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

void Vec3::normalize() {
  double len = length();
  if (len != 0.0) {
    x /= len;
    y /= len;
    z /= len;
  }
}

// Операторы
Vec3 operator+(const Vec3& v1, const Vec3& v2) {
  return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec3 operator-(const Vec3& v1, const Vec3& v2) {
  return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vec3 operator*(const Vec3& v, double scalar) {
  return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

Vec3 operator*(double scalar, const Vec3& v) { return v * scalar; }

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}

// Внешние функции
double dotProduct(const Vec3& v1, const Vec3& v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 crossProduct(const Vec3& v1, const Vec3& v2) {
  return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
              v1.x * v2.y - v1.y * v2.x);
}
