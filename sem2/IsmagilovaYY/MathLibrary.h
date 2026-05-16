#ifndef MATH_LIBRARY_H_
#define MATH_LIBRARY_H_

#include <iostream>

// макрос дл€ экспорта и импорта функций из dll
#ifdef MATH_LIBRARY_EXPORTS
#define MATH_API __declspec(dllexport)  // спецификатор объ€влени€
#else
#define MATH_API __declspec(dllimport)
#endif  // MATH_LIBRARY_EXPORTS

namespace math {

// структура трЄхмерного вектора
struct MATH_API Vec3 {
  float x;
  float y;
  float z;

  Vec3();  // конструктор по умолчанию
  Vec3(float x_val, float y_val, float z_val);

  // перегрузка операторов
  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(float scalar) const;

  // имеет доступ к приватным пол€м
  // выходной поток
  friend MATH_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);
};
// сложение
MATH_API Vec3 add(const Vec3& a, const Vec3& b);

// вычитание
MATH_API Vec3 subtract(const Vec3& a, const Vec3& b);

// умножение на скал€р
MATH_API Vec3 multiply(const Vec3& vec, float scalar);

// скал€рное произведение
MATH_API float sp(const Vec3& a, const Vec3& b);

// векторное произведение
MATH_API Vec3 vp(const Vec3& a, const Vec3& b);

// вычисление длины
MATH_API float length(const Vec3& vec);

// нормализаци€
MATH_API Vec3 normalize(const Vec3& vec);
}  // namespace math

#endif  // MATH_LIBRARY_H_
