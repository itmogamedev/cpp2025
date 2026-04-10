#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>  // Для перегрузки оператора <<

struct MATHLIBRARY_API Vec3 {
  float x_coord;
  float y_coord;
  float z_coord;

  // Конструкторы
  Vec3();
  Vec3(float x, float y, float z);

  // Операторы
  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(float scalar) const;  // Умножение на скаляр
  friend MATHLIBRARY_API Vec3 operator*(float scalar, const Vec3& vec);  // Для скаляр * вектор

  // Методы
  float dotProduct(const Vec3& other) const;
  Vec3 crossProduct(const Vec3& other) const;
  float length() const;
  Vec3 normalize() const;
};

// Перегрузка оператора вывода для Vec3
MATHLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);