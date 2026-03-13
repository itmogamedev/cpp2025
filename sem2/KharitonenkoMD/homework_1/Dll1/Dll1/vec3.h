#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>

struct MATHLIBRARY_API Vec3 {
  float x_comp, y_comp, z_comp;

  // Конструкторы
  Vec3();
  Vec3(float x, float y, float z);

  // Методы
  float getLength() const;
  Vec3 normalize() const;
  float dotProduct(const Vec3& other) const;
  Vec3 crossProduct(const Vec3& other) const;

  // Операторы
  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  float operator*(const Vec3& other) const;
};

// Вывод в поток
MATHLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);
