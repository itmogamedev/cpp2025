#ifndef VEC3_VEC3_H_
#define VEC3_VEC3_H_

#ifdef VEC3_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

#include <iostream>

extern "C" struct Vec3 {
  double x, y, z;

  DECLSPEC Vec3(double x = 0, double y = 0, double z = 0);

  // Операции со скалярами
  DECLSPEC Vec3 operator*(const double scalar) const;
  DECLSPEC Vec3 operator/(const double scalar) const;

  // Операции с векторами
  DECLSPEC Vec3 operator+(const Vec3& other) const;
  DECLSPEC Vec3 operator-(const Vec3& other) const;

  DECLSPEC double dot(const Vec3& other) const;
  DECLSPEC double operator*(const Vec3& other) const;

  DECLSPEC Vec3 cross(const Vec3& other) const;
  DECLSPEC Vec3 operator^(const Vec3& other) const;

  // Операции на себе
  DECLSPEC double length() const;
  DECLSPEC Vec3 normalized() const;
};

extern "C" DECLSPEC std::ostream& operator<<(std::ostream& os, const Vec3& v);

#endif // VEC3_VEC3_H_
