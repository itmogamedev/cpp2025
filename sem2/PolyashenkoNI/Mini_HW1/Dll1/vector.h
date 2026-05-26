#pragma once

#ifdef VEC3LIB_EXPORTS
#define VEC3LIB __declspec(dllexport)
#else
#define VEC3LIB __declspec(dllimport)
#endif

#include <iostream>

class VEC3LIB Vec3 {
 public:
  float x, y, z;
  Vec3(float x = 0, float y = 0, float z = 0);

  friend VEC3LIB Vec3 operator+(const Vec3& a, const Vec3& b);
  friend VEC3LIB Vec3 operator-(const Vec3& a, const Vec3& b);
  friend VEC3LIB Vec3 operator*(const Vec3& vec, float scal);
  friend VEC3LIB Vec3 operator*(float scal, const Vec3& vec);
  friend VEC3LIB std::ostream& operator<<(std::ostream& os, const Vec3& vec);

  float lenght() const;
  void normalizator();
  Vec3 normalezd() const;
  float scalyarMulti(const Vec3& second) const;
  Vec3 veñMulti(const Vec3& second);
};
