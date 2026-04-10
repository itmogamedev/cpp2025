
#include "pch.h"

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}
Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}
Vec3::Vec3(const Vec3& other) : x(other.x), y(other.y), z(other.z) {}

// Сложение векторов
Vec3 Vec3::add(Vec3& other) {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

// Вычитание векторов
Vec3 Vec3::subtract(Vec3& other) {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

// Умножение на скаляр
Vec3 Vec3::multiply(double scalar) {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

// Скалярное произведение
double Vec3::dot(Vec3& other) {
  return x * other.x + y * other.y + z * other.z;
}

// Векторное произведение
Vec3 Vec3::cross(Vec3& other) {
  return Vec3(y * other.z - z * other.y, z * other.x - x * other.z,
              x * other.y - y * other.x);
}

// Длина вектора
double Vec3::length() { return std::sqrt(x * x + y * y + z * z); }

// Нормализация вектора
Vec3 Vec3::normalize() {
  double len = length();
  if (len > 0) {
    return Vec3(x / len, y / len, z / len);
  }
  return Vec3(0, 0, 0);
}

Vec3 Vec3::operator+(Vec3& other) { return add(other); }
Vec3 Vec3::operator-(Vec3& other) { return subtract(other); }
Vec3 Vec3::operator*(double scalar) { return multiply(scalar); }

std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
  os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return os;
}
