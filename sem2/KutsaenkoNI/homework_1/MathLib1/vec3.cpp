#include "vec3.h"

#include <cmath>

namespace mathlib {

Vec3::Vec3() : x_(0.0), y_(0.0), z_(0.0) {}

Vec3::Vec3(double x, double y, double z) : x_(x), y_(y), z_(z) {}

// Скалярное произведение
double Vec3::dot(const Vec3& other) const {
  return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
}

// Векторное произведение
Vec3 Vec3::cross(const Vec3& other) const {
  return Vec3(y_ * other.z_ - z_ * other.y_, z_ * other.x_ - x_ * other.z_,
              x_ * other.y_ - y_ * other.x_);
}

// Длина вектора
double Vec3::length() const { return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_); }

// Нормализация вектора
Vec3 Vec3::normalize() const {
  double len = length();
  if (len > 0.0) {
    return Vec3(x_ / len, y_ / len, z_ / len);
  }
  return Vec3();
}

// Сложение
Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
  return Vec3(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_, lhs.z_ + rhs.z_);
}

// Вычитание
Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
  return Vec3(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_, lhs.z_ - rhs.z_);
}

// Умножение: вектор на скаляр
Vec3 operator*(const Vec3& vec, double scalar) {
  return Vec3(vec.x_ * scalar, vec.y_ * scalar, vec.z_ * scalar);
}

// Умножение: скаляр на вектор
Vec3 operator*(double scalar, const Vec3& vec) {
  return Vec3(vec.x_ * scalar, vec.y_ * scalar, vec.z_ * scalar);
}

std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
  os << "Vec3(" << vec.x_ << ", " << vec.y_ << ", " << vec.z_ << ")";
  return os;
}

}  // namespace mathlib
