// vec3.cpp

#include "pch.h"

#include <limits.h>

#include <utility>

#include "vec3.h"

// use stdafx.h in Visual Studio 2017 and earlier

// Конструктор
Vec3::Vec3(float x_val, float y_val, float z_val)
    : x(x_val), y(y_val), z(z_val) {}

// Длина вектора
float Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

// Нормализация на месте
void Vec3::normalize() {
  float len = length();
  if (len > 1e-8f)  // защита от деления на очень маленькое число
  {
    x /= len;
    y /= len;
    z /= len;
  } else {
    x = y = z = 0.0f;
  }
}

// Нормализованная копия
Vec3 Vec3::normalized() const {
  Vec3 result = *this;
  result.normalize();
  return result;
}

// Скалярное произведение
float Vec3::dot(const Vec3& other) const {
  return x * other.x + y * other.y + z * other.z;
}

// Векторное произведение
Vec3 Vec3::cross(const Vec3& other) const {
  return Vec3(y * other.z - z * other.y, z * other.x - x * other.z,
              x * other.y - y * other.x);
}

// ───────────────────────────────────────────────
// Свободные операторы

Vec3 operator+(const Vec3& a, const Vec3& b) {
  return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
  return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator*(const Vec3& v, float scalar) {
  return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

Vec3 operator*(float scalar, const Vec3& v) { return v * scalar; }

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}
