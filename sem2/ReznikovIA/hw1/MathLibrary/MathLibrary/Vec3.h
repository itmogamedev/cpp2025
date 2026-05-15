#pragma once
#include <ostream>
#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

struct MATHLIBRARY_API Vec3 {
 public:
  float x;
  float y;
  float z;

  Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
  Vec3 operator+(const Vec3& second) const;
  Vec3 operator-(const Vec3& second) const;
  Vec3 operator*(float scalar) const;
  float dot(const Vec3& second) const;
  Vec3 cross(const Vec3& second) const;
  float length() const;
  Vec3 normalized() const;
  friend MATHLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& v);
};
