#include "pch.h"
#include "vector3D.h"

#include <cmath>

Vector3D::Vector3D() : x(0), y(0), z(0) {}
Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

double Vector3D::dotProd(const Vector3D& other) const {
  return (x * other.x + y * other.y + z * other.z);
}

Vector3D Vector3D::vecProd(const Vector3D& other) const {
  return Vector3D(y * other.z - z * other.y, z * other.x - x * other.z,
                  x * other.y - y * other.x);
}

double Vector3D::lenghtVec() const { return (sqrt(x * x + y * y + z * z)); }

Vector3D Vector3D::normVec() const {
  double len = lenghtVec();
  if (len != 0) {
    return (Vector3D(x / len, y / len, z / len));
  } else {
    return Vector3D(0, 0, 0);
  }
}

Vector3D Vector3D::operator+(const Vector3D& other) const {
  return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D& other) const {
  return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator*(double scalar) const {
  return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D operator*(double scalar, const Vector3D& vec) {
    return (vec * scalar);
}

std::ostream& operator<<(std::ostream& os, const Vector3D& vec) {
  os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return os;
}