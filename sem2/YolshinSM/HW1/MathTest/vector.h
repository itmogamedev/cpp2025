#pragma once

#ifdef MATHLIBSALDAW_EXPORTS
#define VEC3_API __declspec(dllexport)
#else
#define VEC3_API __declspec(dllimport)
#endif

#include <cmath>
#include <iostream>

class VEC3_API Vec3 {
 public:
  double x, y, z;
  Vec3();
  Vec3(double x, double y, double z);
  Vec3(const Vec3& other);

  Vec3 add(Vec3& other);
  Vec3 subtract(Vec3& other);
  Vec3 multiply(double scalar);
  double dot(Vec3& other);
  Vec3 cross(Vec3& other);
  double length();
  Vec3 normalize();

  Vec3 operator+(Vec3& other);
  Vec3 operator-(Vec3& other);
  Vec3 operator*(double scalar);
};

VEC3_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);
