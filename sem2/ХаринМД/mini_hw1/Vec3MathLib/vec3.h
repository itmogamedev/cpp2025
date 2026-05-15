#ifndef VEC3_H
#define VEC3_H

#include <iostream>

struct Vec3 {
  double x;
  double y;
  double z;

  Vec3();
  Vec3(double x_val, double y_val, double z_val);

  double length() const;
  Vec3 normalize() const;

  static double dot(const Vec3& a, const Vec3& b);
  static Vec3 cross(const Vec3& a, const Vec3& b);

  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(double scalar) const;
};

std::ostream& operator<<(std::ostream& os, const Vec3& v);

#endif