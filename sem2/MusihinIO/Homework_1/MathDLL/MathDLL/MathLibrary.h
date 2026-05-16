// MathLibrary.h - Contains declarations of math functions
#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>

struct MATHLIBRARY_API Vec3 {
  double x;
  double y;
  double z;

  Vec3();
  Vec3(double x, double y, double z);

  Vec3 add(const Vec3& other) const;
  Vec3 subtract(const Vec3& other) const;

  Vec3 multiply(double scalar) const;

  double dot(const Vec3& other) const;

  Vec3 cross(const Vec3& other) const;

  double length() const;

  Vec3 normalize() const;
};

MATHLIBRARY_API Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
MATHLIBRARY_API Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
MATHLIBRARY_API Vec3 operator*(const Vec3& vec, double scalar);
MATHLIBRARY_API Vec3 operator*(double scalar, const Vec3& vec);
MATHLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);
