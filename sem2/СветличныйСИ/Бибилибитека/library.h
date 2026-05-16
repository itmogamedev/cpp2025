#ifndef MYLIB_H
#define MYLIB_H

#ifdef _WIN32
#ifdef MYLIB_EXPORTS
#define MYLIB_API __declspec(dllexport)
#else
#define MYLIB_API __declspec(dllimport)
#endif
#else
#define MYLIB_API __attribute__((visibility("default")))
#endif

#include <iostream>

class MYLIB_API Vec3 {
public:
  double x, y, z;

  Vec3() : x(0), y(0), z(0)
  {
  }

  Vec3(double x, double y, double z) : x(x), y(y), z(z)
  {
  }

  Vec3 operator+(const Vec3 &other) const;

  Vec3 operator-(const Vec3 &other) const;

  double operator*(const Vec3 &other) const;

  Vec3 operator*(double a) const;

  Vec3 operator^(Vec3 other) const;

  friend std::ostream &operator<<(std::ostream &os, const Vec3 &p);

  double length();

  Vec3 normalize();
};

MYLIB_API std::ostream &operator<<(std::ostream &os, const Vec3 &p);

#endif
