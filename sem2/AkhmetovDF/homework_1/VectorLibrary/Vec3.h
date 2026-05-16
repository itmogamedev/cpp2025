#pragma once

#include <iostream>

#ifdef DLL1_EXPORTS
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllimport)
#endif

// структура, представляющая трёхмерный вектор
struct MATH_API Vec3 {
  double x, y, z;  // компоненты вектора

  // конструктор с параметрами по умолчанию
  Vec3(double x = 0.0, double y = 0.0, double z = 0.0);

  // арифметические операции
  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(double scalar) const;

  // операции с вектором
  double length() const;  // длина вектора
  void normalize();       // нормализация вектора
};

// умножение числа на вектор
MATH_API Vec3 operator*(double scalar, const Vec3& v);

// скалярное произведение
MATH_API double dot(const Vec3& a, const Vec3& b);

// векторное произведение
MATH_API Vec3 cross(const Vec3& a, const Vec3& b);

// вывод в поток
MATH_API std::ostream& operator<<(std::ostream& os, const Vec3& v);
