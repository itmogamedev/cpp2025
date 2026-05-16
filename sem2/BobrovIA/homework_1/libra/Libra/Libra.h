#pragma once
#include <iostream>

#ifdef LIBRA_EXPORTS
#define LIBRA_API __declspec(dllexport)
#else
#define LIBRA_API __declspec(dllimport)
#endif

struct LIBRA_API Vec3 {
  float x, y, z;

  Vec3(float x = 0, float y = 0, float z = 0);

  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  float operator*(const Vec3& other) const;
  Vec3 operator*(float scalar) const;

  float length() const;
  Vec3 normalize() const;
  Vec3 cross(const Vec3& other) const;

  friend LIBRA_API std::ostream& operator<<(std::ostream& output, const Vec3& v);
};
