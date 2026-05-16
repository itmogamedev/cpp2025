#ifndef MATHLIBRARY_MATHLIBRARY_H_
#define MATHLIBRARY_MATHLIBRARY_H_

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>

struct MATHLIBRARY_API Vec3 {
  float x;
  float y;
  float z;

  Vec3();
  Vec3(float x, float y, float z);
};

MATHLIBRARY_API Vec3 add(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 subtract(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 multiplyByScalar(const Vec3& v, float scalar);
MATHLIBRARY_API float dotProduct(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 crossProduct(const Vec3& a, const Vec3& b);
MATHLIBRARY_API float length(const Vec3& v);
MATHLIBRARY_API Vec3 normalize(const Vec3& v);

MATHLIBRARY_API Vec3 operator+(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 operator-(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 operator*(const Vec3& v, float scalar);
MATHLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& v);

#endif  // MATHLIBRARY_MATHLIBRARY_H_
