
#include "MiniLib.h"

#include <cmath>
#include <iostream>
// Конструкторы
Vec3::Vec3() : x(0), y(0), z(0) {}
Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

// Сложение с другим вектором (возвращает новый вектор)
Vec3 Vec3::additionVec(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

// Вычитание другого вектора
Vec3 Vec3::subtraction(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

// Умножение на скаляр
Vec3 Vec3::multScalar(double scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

// Скалярное произведение
double Vec3::dotProduct(const Vec3& other) const {
  return x * other.x + y * other.y + z * other.z;
}

// Длина вектора
double Vec3::lengthVec() const { return std::sqrt(x * x + y * y + z * z); }

// Векторное произведение
Vec3 Vec3::vectorProduct(const Vec3& other) const {
  return Vec3(y * other.z - z * other.y, z * other.x - x * other.z,
              x * other.y - y * other.x);
}

// Нормализация (изменяет текущий вектор)
void Vec3::normalize() {
  double len = lengthVec();
  if (len > 0) {
    x /= len;
    y /= len;
    z /= len;
  }
}

// Возвращает нормализованную копию (не изменяет текущий)
Vec3 Vec3::normalized() const {
  Vec3 res = *this;
  res.normalize();
  return res;
}

// Перегрузка операторов (для удобства)
Vec3 Vec3::operator+(const Vec3& other) const { return additionVec(other); }

Vec3 Vec3::operator-(const Vec3& other) const { return subtraction(other); }

Vec3 Vec3::operator*(double scalar) const { return multScalar(scalar); }
// Умножение на скаляр слева (дружественная функция)
Vec3 operator*(double scalar, const Vec3& v) { return v * scalar; }

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}
