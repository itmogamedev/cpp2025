#ifndef MATHLIBRARY_MATH_H_
#define MATHLIBRARY_MATH_H_

#ifdef MATHLIBRARY_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

#include "pch.h"

extern "C" struct Vec3 {
  double x, y, z;

  DECLSPEC Vec3(double x = 0, double y = 0, double z = 0);
  DECLSPEC Vec3 addVec(Vec3 a);
  DECLSPEC Vec3 subVec(Vec3 a);
  DECLSPEC Vec3 multiplicVec(double scal);
  DECLSPEC double dotProd(Vec3 a);
  DECLSPEC Vec3 crossProd(Vec3 a);
  DECLSPEC double lenVec();
  DECLSPEC Vec3 normVec();

  DECLSPEC Vec3 operator+(const Vec3& a);
  DECLSPEC Vec3 operator-(const Vec3& a);
  DECLSPEC double operator*(const Vec3& a);
  DECLSPEC Vec3 operator*(const double& a);
};

extern "C" DECLSPEC std::ostream& operator<<(std::ostream& os, const Vec3& a);

#endif  // MATHLIBRARY_MATH_H_
