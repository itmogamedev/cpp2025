#pragma once
#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>

class MATHLIBRARY_API Vec3 {
 public:
  float x, y, z;

  Vec3();
  Vec3(float x, float y, float z);

  Vec3 operator+(Vec3 v);
  Vec3 operator-(Vec3 v);
  Vec3 operator*(float n);

  float scalarMulti(Vec3 v);
  Vec3 vectorMulti(Vec3 v);
  float vectorLength();
  Vec3 normal();
};

MATHLIBRARY_API std::ostream& operator<<(std::ostream&, Vec3&);
