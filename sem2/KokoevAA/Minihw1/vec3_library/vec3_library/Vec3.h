#ifndef VEC3_H
#define VEC3_H

#include <iostream>

#ifdef VEC3LIBRARY_EXPORTS
#define VEC3_API __declspec(dllexport)
#else
#define VEC3_API __declspec(dllimport)
#endif

class VEC3_API Vec3 {
 public:
  double x;
  double y;
  double z;

  Vec3();
  Vec3(double x_value, double y_value, double z_value);

  Vec3 add(const Vec3& other) const;
  Vec3 subtract(const Vec3& other) const;
  Vec3 multiplyByScalar(double scalar) const;

  double scalarMultiply(const Vec3& other) const;
  Vec3 vectorMultiply(const Vec3& other) const;

  double length() const;
  Vec3 normalize() const;

  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(double scalar) const;
};

VEC3_API std::ostream& operator<<(std::ostream& out, const Vec3& vec);

#endif
