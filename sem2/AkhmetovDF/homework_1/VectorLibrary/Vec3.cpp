#include "Vec3.h"

#include "pch.h"

// конструктор
Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

// сложение
Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

// вычитание
Vec3 Vec3::operator-(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

// умножение вектора на число
Vec3 Vec3::operator*(double scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

// умножение числа на вектор
Vec3 operator*(double scalar, const Vec3& v) {
  return v * scalar;  // использует уже определённый оператор
}

// вывод в поток
std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}

// длина вектора
double Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

// нормализация вектора
void Vec3::normalize() {
  double len = length();
  if (len > 1e-12) {
    x /= len;
    y /= len;
    z /= len;
  }
}

// скалярное произведение
double dot(const Vec3& a, const Vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

// векторное произведение
Vec3 cross(const Vec3& a, const Vec3& b) {
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}
