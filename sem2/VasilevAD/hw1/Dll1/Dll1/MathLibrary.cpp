#define MATHLIBRARY_EXPORTS

#include "pch.h"
#include "MathLibrary.h"
#include <cmath>

// Конструкторы
Vec3::Vec3() : x_coord(0.0f), y_coord(0.0f), z_coord(0.0f) {}
Vec3::Vec3(float x, float y, float z) : x_coord(x), y_coord(y), z_coord(z) {}

//сложение
Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x_coord + other.x_coord, y_coord + other.y_coord, z_coord + other.z_coord);
}

//вычитание
Vec3 Vec3::operator-(const Vec3& other) const{
  return Vec3(x_coord - other.x_coord, y_coord - other.y_coord, z_coord - other.z_coord);
}

//умножение на скаляр
Vec3 Vec3::operator*(float scalar) const {
  return Vec3(x_coord * scalar, y_coord * scalar, z_coord * scalar);
}
MATHLIBRARY_API Vec3 operator*(float scalar, const Vec3& vec) {
  return Vec3(vec.x_coord * scalar, vec.y_coord * scalar, vec.z_coord * scalar);
}

//скалярное произведение
float Vec3::dotProduct(const Vec3& other) const {
  return x_coord * other.x_coord + y_coord * other.y_coord + z_coord * other.z_coord;
}

//векторное произведение
Vec3 Vec3::crossProduct(const Vec3& other) const {
  return Vec3(y_coord * other.z_coord - z_coord * other.y_coord,
              z_coord * other.x_coord - x_coord * other.z_coord,
              x_coord * other.y_coord - y_coord * other.x_coord);
}

//длина
float Vec3::length() const {
  return std::sqrt(x_coord * x_coord + y_coord * y_coord + z_coord * z_coord);
}

//нормализация
Vec3 Vec3::normalize() const {
  float len = length();
  if (len == 0.0f) {
    return Vec3(0.0f, 0.0f, 0.0f);
  }
  return Vec3(x_coord / len, y_coord / len, z_coord / len);
}

// Перегрузка оператора вывода для Vec3
MATHLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
  os << "(" << vec.x_coord << ", " << vec.y_coord << ", " << vec.z_coord << ")";
  return os;
}