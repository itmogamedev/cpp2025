#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>

struct MATHLIBRARY_API Vec3 {
  double x, y, z;

  Vec3(double x = 0, double y = 0, double z = 0);
};

MATHLIBRARY_API Vec3 operator+(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 operator-(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 operator*(const Vec3& v, double scalar);
MATHLIBRARY_API Vec3 operator*(double scalar, const Vec3& v);
MATHLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& v);
MATHLIBRARY_API double scalarProduct(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 vectorProduct(const Vec3& a, const Vec3& b);
MATHLIBRARY_API double vectorLength(const Vec3& v);
MATHLIBRARY_API Vec3 normalizeVector(const Vec3& v);
