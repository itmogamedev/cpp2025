#pragma once
#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif
#include <ostream>
extern "C" MATHLIBRARY_API class Vec3 {
 public:
  float x;
  float y;
  float z;
  Vec3(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
  }
  Vec3 operator+(const Vec3& b) { return Vec3(x + b.x, y + b.y, z + b.z); }
  Vec3 operator-(const Vec3& b) { return Vec3(x - b.x, y - b.y, z - b.z); }
  Vec3 operator*(const float& n) { return Vec3(x * n, y * n, z * n); }
  int ScalarMultiplication(const Vec3& b) {
    return x * b.x + y * b.y + z * b.z;
  }
  Vec3 VectorMultiplication(Vec3 b) {
    return Vec3(y * b.z - z * b.y, x * b.z - z * b.x, x * b.y - y * b.x);
  }
};
extern "C" MATHLIBRARY_API std::ostream& operator<<(std::ostream& o, Vec3 a) {
  return o << a.x << " " << a.y << " " << a.z;
}

