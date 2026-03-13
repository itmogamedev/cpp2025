#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>

namespace MathLibrary {
// Структура трехмерного вектора
struct MATHLIBRARY_API Vec3 {
  double x, y, z;

  // Конструкторы
  Vec3();
  Vec3(double x, double y, double z);
  Vec3(const Vec3& other);

  // Операторы
  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(double scalar) const;
  friend Vec3 operator*(double scalar, const Vec3& vec);
  double operator*(const Vec3& other) const;  // Скалярное произведение
  friend std::ostream& operator<<(std::ostream& os, const Vec3& vec);
};

// Функции для работы с векторами
extern "C" {
MATHLIBRARY_API Vec3 AddVectors(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 SubtractVectors(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 MultiplyByScalar(const Vec3& vec, double scalar);
MATHLIBRARY_API double DotProduct(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 CrossProduct(const Vec3& a, const Vec3& b);
MATHLIBRARY_API double VectorLength(const Vec3& vec);
MATHLIBRARY_API Vec3 NormalizeVector(const Vec3& vec);
}
}  // namespace MathLibrary
