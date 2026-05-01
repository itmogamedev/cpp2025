#ifndef MATHLIBRARY_VEC3_H_
#define MATHLIBRARY_VEC3_H_

#include <iostream>

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

class MATHLIBRARY_API Vec3 {
 public:
  double x, y, z;

  Vec3();
  Vec3(double x_val, double y_val, double z_val);

  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(double scalar) const;

  double dot(const Vec3& other) const;
  Vec3 cross(const Vec3& other) const;

  double length() const;
  Vec3 normalized() const;
};

MATHLIBRARY_API Vec3 operator*(double scalar, const Vec3& vec);
MATHLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);

#endif
