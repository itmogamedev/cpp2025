#ifndef MINILIB_H
#define MINILIB_H

#include <iostream>

#ifdef _WIN32
#ifdef BUILDING_MINI_LIB
#define MINILIB_API __declspec(dllexport)
#else
#define MINILIB_API __declspec(dllimport)
#endif
#else
#define MINILIB_API
#endif

struct MINILIB_API Vec3 {
  double x, y, z;

  Vec3();
  Vec3(double x, double y, double z);

  Vec3 additionVec(const Vec3& other) const;
  Vec3 subtraction(const Vec3& other) const;
  Vec3 multScalar(double scalar) const;
  double dotProduct(const Vec3& other) const;
  double lengthVec() const;
  Vec3 vectorProduct(const Vec3& other) const;
  void normalize();
  Vec3 normalized() const;

  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(double scalar) const;
};

MINILIB_API Vec3 operator*(double scalar, const Vec3& v);
MINILIB_API std::ostream& operator<<(std::ostream& os, const Vec3& v);

#endif  // !MiniLib.h
