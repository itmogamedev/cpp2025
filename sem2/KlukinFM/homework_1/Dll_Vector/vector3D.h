#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

#ifdef _WIN32
#ifdef BUILDING_VECTRO3D
#define VECTOR3D_API __declspec(dllexport)
#else
#define VECTOR3D_API __declspec(dllimport)
#endif  // BUILDING_VECTROR3D
#else
#define VECTOR3D_API
#endif  // _WIN32

struct VECTOR3D_API Vector3D {
  double x, y, z;

  Vector3D();
  Vector3D(double x, double y, double z);

  double dotProd(const Vector3D& other) const;
  Vector3D vecProd(const Vector3D& other) const;
  double lenghtVec() const;
  Vector3D normVec() const;

  Vector3D operator+(const Vector3D& other) const;
  Vector3D operator-(const Vector3D& other) const;
  Vector3D operator*(double scalar) const;
};

VECTOR3D_API Vector3D operator*(double scalar, const Vector3D& vec);
VECTOR3D_API std::ostream& operator<<(std::ostream& os, const Vector3D& vector);

#endif