#include "vector_lib.h"

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

// Сложение
Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

// Вычитание
Vec3 Vec3::operator-(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

// Скалярное произведение
float Vec3::operator*(const Vec3& other) const {
  return x * other.x + y * other.y + z * other.z;
}

// Векторное произведение
Vec3 Vec3::operator^(const Vec3& other) const {
  return Vec3(y * other.z - z * other.y, z * other.x - x * other.z,
              x * other.y - y * other.x);
}

// Длина
float Vec3::length() const { return std::sqrt(x * 2 + y * 2 + z * 2); }

// Нормализация
Vec3 Vec3::normalize() const {
  float len = length();
  if (len > 0) {
    return Vec3(x / len, y / len, z / len);
  }
  return *this;
}

// Умножение вектора на число и число на вектор
Vec3 operator*(const Vec3& v, float scalar) {
  return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}
Vec3 operator*(float scalar, const Vec3& v) {
  return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

// Вывод
std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
  return os;
}
