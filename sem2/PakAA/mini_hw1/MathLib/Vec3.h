#pragma once

#ifdef MATHLIB_EXPORTS
#define MATHLIB_API __declspec(dllexport)
#else
#define MATHLIB_API __declspec(dllimport)
#endif

#include <cmath>
#include <ostream>

struct MATHLIB_API Vec3 {
  float x, y, z;

  Vec3(float x = 0.f, float y = 0.f, float z = 0.f);

  // Сложение / вычитание
  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;

  // Умножение на скаляр
  Vec3 operator*(float scalar) const;

  // Вывод
  friend MATHLIB_API std::ostream& operator<<(std::ostream& os, const Vec3& v);
};

// Скалярное произведение
MATHLIB_API float dot(const Vec3& a, const Vec3& b);

// Векторное произведение
MATHLIB_API Vec3 cross(const Vec3& a, const Vec3& b);

// Длина вектора
MATHLIB_API float length(const Vec3& v);

// Нормализация
MATHLIB_API Vec3 normalize(const Vec3& v);
