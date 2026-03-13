#pragma once
#include <iostream>
// для использования одного и того же h файла для экспорта и импорта функций из
// dll

#ifdef VECTLIB_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif

struct VECTOR_API Vec3 {
  double x, y, z;

  // перегрузка операторов
  Vec3 operator+(const Vec3& other) const;  //& - ссылка
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(double scalar) const;
  Vec3 operator/(double scalar) const;
};

// +/-
VECTOR_API Vec3 plusVectors(const Vec3& v1, const Vec3& v2);

VECTOR_API Vec3 minusVectors(const Vec3& v1, const Vec3& v2);

// скалярное произведение
VECTOR_API double dotProduct(const Vec3& v1, const Vec3& v2);

// векторное произведение
VECTOR_API Vec3 vectorProduct(const Vec3& v1, const Vec3& v2);

// длина
VECTOR_API double vectorLength(const Vec3& v);

// нормализация
VECTOR_API Vec3 vectorNormalize(const Vec3& v);

// перегрузка оператора вывода
VECTOR_API std::ostream& operator<<(std::ostream& os, const Vec3& v);
