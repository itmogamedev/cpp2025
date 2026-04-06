#pragma once

#ifdef MATH_VECTOR_EXPORTS
#define MATH_VECTOR_API __declspec(dllexport)
#else
#define MATH_VECTOR_API __declspec(dllimport)
#endif

#include <iostream>

struct MATH_VECTOR_API Vec3 {
  double x, y, z;

  Vec3();
  Vec3(double x, double y, double z);
  Vec3(const Vec3& other);

  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(double scalar) const;
};

MATH_VECTOR_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);
MATH_VECTOR_API Vec3 operator*(double scalar, const Vec3& vec);

MATH_VECTOR_API Vec3 Add(const Vec3& a, const Vec3& b);
MATH_VECTOR_API Vec3 Subtract(const Vec3& a, const Vec3& b);
MATH_VECTOR_API Vec3 Multiply(const Vec3& vec, double scalar);
MATH_VECTOR_API double DotProduct(const Vec3& a, const Vec3& b);
MATH_VECTOR_API Vec3 CrossProduct(const Vec3& a, const Vec3& b);
MATH_VECTOR_API double Length(const Vec3& vec);
MATH_VECTOR_API Vec3 Normalize(const Vec3& vec);
