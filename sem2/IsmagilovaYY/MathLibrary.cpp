#include "MathLibrary.h"

#include <cmath>

namespace math {

// конструкторы
Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

Vec3::Vec3(float x_val, float y_val, float z_val)
    : x(x_val), y(y_val), z(z_val) {}

// перегрузка операторов
Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(float scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

MATH_API std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
  os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return os;
}

// реализация функций
// сложение
Vec3 add(const Vec3& a, const Vec3& b) { return a + b; }

// вычитание
Vec3 subtract(const Vec3& a, const Vec3& b) { return a - b; }

// умножение на скаляр
Vec3 multiply(const Vec3& vec, float scalar) { return vec * scalar; }

// скалярное умножение
float sp(const Vec3& a, const Vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

// векторное умножение
Vec3 vp(const Vec3& a, const Vec3& b) {
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

// вычисление длины
float length(const Vec3& vec) { return std::sqrt(sp(vec, vec)); }

// нормализация
Vec3 normalize(const Vec3& vec) {
  float len = length(vec);
  if (len > 0.0f) {
    return vec * (1.0f / len);
  }
  return Vec3();
}

}  // namespace math
