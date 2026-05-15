#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>

struct MATHLIBRARY_API Vec3 {
  double x, y, z;

  Vec3(double x = 0.0, double y = 0.0, double z = 0.0);

  Vec3(const Vec3& other);

  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(double scalar) const;
  Vec3 operator/(double scalar) const;
};

MATHLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& v);

MATHLIBRARY_API Vec3 add(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 subtract(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 multiply_scalar(const Vec3& v, double scalar);
MATHLIBRARY_API double dot_product(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 cross_product(const Vec3& a, const Vec3& b);
MATHLIBRARY_API double vector_length(const Vec3& v);
MATHLIBRARY_API Vec3 normalize_vector(const Vec3& v);
