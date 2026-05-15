#ifndef VEC3_H_
#define VEC3_H_

#ifdef VEC3LIBRARY_EXPORTS
#define MATHLIB __declspec(dllexport)
#else
#define MATHLIB __declspec(dllimport)
#endif

#include <ostream>

namespace math {

struct MATHLIB Vec3 {
  double x;
  double y;
  double z;

  Vec3();
  Vec3(double x_value, double y_value, double z_value);

  double Length() const;

  Vec3 Normalized() const;
};

MATHLIB Vec3 operator+(const Vec3& a, const Vec3& b);
MATHLIB Vec3 operator-(const Vec3& a, const Vec3& b);

MATHLIB Vec3 operator*(const Vec3& v, double scalar);
MATHLIB Vec3 operator*(double scalar, const Vec3& v);

MATHLIB double Dot(const Vec3& a, const Vec3& b);

MATHLIB Vec3 Cross(const Vec3& a, const Vec3& b);

MATHLIB std::ostream& operator<<(std::ostream& out, const Vec3& v);

}  // namespace math

#endif
