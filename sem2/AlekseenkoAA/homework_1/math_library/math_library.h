#pragma once

#include <iostream>

/*
"Новый шаблон проекта для библиотеки DLL добавляет <PROJECTNAME>_EXPORTS к
определённым макросам препроцессора. В этом примере Visual Studio определяет
MATHLIBRARY_EXPORTS , когда создается проект DLL".
https://learn.microsoft.com/ru-ru/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170
*/

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API \
  __declspec(dllexport)  // если заголовочный файл собирается как библеотека,
                         // препроцессор подставить dllexport для использования
                         // в приложениях
#else
#define MATHLIBRARY_API \
  __declspec(dllimport)  // если заголовочный файл собирается как исполняемый
                         // файл, препроцессор подставить dllimpirt для
                         // использования в приложении соотвественно
#endif

struct Vec3 {
  long double x;
  long double y;
  long double z;

  Vec3() : x(0.0L), y(0.0L), z(0.0L) {};
  Vec3(long double x, long double y, long double z) : x(x), y(y), z(z) {}
  ~Vec3() = default;
};

struct Matrix2x2 {
  // a b (0 1
  // c d  2 3)
  long double mat[4];

  Matrix2x2() : mat{0.0L, 0.0L, 0.0L, 0.0L} {};
  Matrix2x2(long double a, long double b, long double c, long double d)
      : mat{a, b, c, d} {}
  ~Matrix2x2() = default;
};

struct Matrix3x3 {
  // a b c (0 1 2
  // d e f  3 4 5
  // g k l  6 7 8)
  long double mat[9];

  Matrix3x3() : mat{0.0L, 0.0L, 0.0L, 0.0L, 0.0L, 0.0L, 0.0L, 0.0L, 0.0L} {};
  Matrix3x3(long double a, long double b, long double c, long double d,
            long double e, long double f, long double g, long double k,
            long double l)
      : mat{a, b, c, d, e, f, g, k, l} {}
  Matrix3x3(const Vec3& vec_1, const Vec3& vec_2, const Vec3& vec_3)
      : mat{vec_1.x, vec_1.y, vec_1.z, vec_2.x, vec_2.y,
            vec_2.z, vec_3.x, vec_3.y, vec_3.z} {}
  ~Matrix3x3() = default;
};

const Vec3 unit_vector = Vec3(1.0L, 1.0L, 1.0L);

// сложение (a)
MATHLIBRARY_API Vec3 addVec3(const Vec3& vec_1, const Vec3& vec_2);
// вычитание (a)
MATHLIBRARY_API Vec3 subVec3(const Vec3& vec_1, const Vec3& vec_2);

// умножение вектора на скаляр (b)
MATHLIBRARY_API Vec3 mulVec3(long double x, const Vec3& vec);

// деление вектора на скаляр (b)
MATHLIBRARY_API Vec3 divVec3(long double x, const Vec3& vec);

// Скалярное произведение векторов (c)
MATHLIBRARY_API long double dotVec3(const Vec3& vec_1, const Vec3& vec_2);

// Векторное произведение (d)
MATHLIBRARY_API Vec3 crossVec3(const Vec3& vec_1, const Vec3& vec_2);

// Вычисление нормализация (e.1)
MATHLIBRARY_API Vec3 normVec3(const Vec3& vec);

// Вычесление длины (e.2)
MATHLIBRARY_API long double lenghtVec3(const Vec3& vec);

MATHLIBRARY_API Vec3 operator-(const Vec3& vec, const Vec3& vec_other);

MATHLIBRARY_API Vec3 operator+(const Vec3& vec, const Vec3& vec_other);

MATHLIBRARY_API Vec3 operator*(const Vec3& vec, long double x);
MATHLIBRARY_API Vec3
operator*(long double x,
          const Vec3& vec);  // коммунитативность сама собой не заработает...

MATHLIBRARY_API Vec3 operator/(const Vec3& vec, long double x);

MATHLIBRARY_API Vec3
operator^(const Vec3& vec,
          const Vec3& vec_other);  // для скалярного произведения...

MATHLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);

MATHLIBRARY_API long double detMat2x2(const Matrix2x2& mat);

MATHLIBRARY_API long double detMat3x3(const Matrix3x3& mat);

MATHLIBRARY_API Vec3 detMat3x3Separated(const Matrix3x3& mat);