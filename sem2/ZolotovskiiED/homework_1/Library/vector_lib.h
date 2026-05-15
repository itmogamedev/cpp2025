#pragma once
#include <iostream>

#ifdef VECTORLIB_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif

struct VECTOR_API Vec3 {
  float x, y, z;

  Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

  // Сложение
  Vec3 operator+(const Vec3& other) const;

  // Вычитание
  Vec3 operator-(const Vec3& other) const;

  // Скалярное произведение
  float operator*(const Vec3& other) const;

  // Векторное произведение
  Vec3 operator^(const Vec3& other) const;

  // Длина
  float length() const;

  // Нормализация
  Vec3 normalize() const;
};

// Умножение вектора на число и число на вектор
VECTOR_API Vec3 operator*(const Vec3& v, float scalar);
VECTOR_API Vec3 operator*(float scalar, const Vec3& v);

// Вывод
VECTOR_API std::ostream& operator<<(std::ostream& os, const Vec3& v);
