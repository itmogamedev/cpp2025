#pragma once

// Всё, что нужно — только std::ostream и std::sqrt
#include <cmath>
#include <iostream>

// Экспорт для DLL
#ifdef MATHVECTORLIBRARY_EXPORTS
#define MATHVECTOR_API __declspec(dllexport)
#else
#define MATHVECTOR_API __declspec(dllimport)
#endif

// Структура вектора — без лишнего
struct MATHVECTOR_API Vec3 {
  double x;
  double y;
  double z;

  // Конструктор
  Vec3(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

  // Методы
  double length() const;
  void normalize();
};

// Операторы (все с MATHVECTOR_API)
MATHVECTOR_API Vec3 operator+(const Vec3& v1, const Vec3& v2);
MATHVECTOR_API Vec3 operator-(const Vec3& v1, const Vec3& v2);
MATHVECTOR_API Vec3 operator*(const Vec3& v, double scalar);
MATHVECTOR_API Vec3 operator*(double scalar, const Vec3& v);
MATHVECTOR_API std::ostream& operator<<(std::ostream& os, const Vec3& v);

// Внешние функции
MATHVECTOR_API double dotProduct(const Vec3& v1, const Vec3& v2);
MATHVECTOR_API Vec3 crossProduct(const Vec3& v1, const Vec3& v2);
