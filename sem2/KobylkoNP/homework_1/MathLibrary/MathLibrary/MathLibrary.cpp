#include "MathLibrary.h"

#include <cmath>

const Vec3 Vec3::Zero(0, 0, 0);

// Default constructor
Vec3::Vec3() {
  this->x = 0;
  this->y = 0;
  this->z = 0;
}

// Parameterized constructor
Vec3::Vec3(double x, double y, double z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

// Copy constructor
Vec3::Vec3(const Vec3& other) {
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
}

// Getters
double Vec3::getX() const { return x; }
double Vec3::getY() const { return y; }
double Vec3::getZ() const { return z; }

// Setters
void Vec3::setX(double x) { this->x = x; }
void Vec3::setY(double y) { this->y = y; }
void Vec3::setZ(double z) { this->z = z; }

// Arithmetic operations
Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(double scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

// Scalar multiplication (scalar * vector)
Vec3 operator*(double scalar, const Vec3& vec) { return vec * scalar; }

// Compound assignment
Vec3& Vec3::operator+=(const Vec3& other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

Vec3& Vec3::operator-=(const Vec3& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

Vec3& Vec3::operator*=(double scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

// Dot product
double Vec3::dot(const Vec3& other) const {
  return x * other.x + y * other.y + z * other.z;
}

// Cross product
Vec3 Vec3::cross(const Vec3& other) const {
  return Vec3(y * other.z - z * other.y, z * other.x - x * other.z,
              x * other.y - y * other.x);
}

// Vector length
double Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

// Normalization
Vec3 Vec3::normalize() const {
  double len = length();
  if (len > 0) {
    return Vec3(x / len, y / len, z / len);
  }
  return Zero;
}

// Output operator
std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
  os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return os;
}
