#include "vec3.h"

#include <cmath>

Vec3::Vec3() : x_comp(0), y_comp(0), z_comp(0) {}
Vec3::Vec3(float x, float y, float z) : x_comp(x), y_comp(y), z_comp(z) {}

float Vec3::getLength() const {
  return std::sqrt(x_comp * x_comp + y_comp * y_comp + z_comp * z_comp);
}

Vec3 Vec3::normalize() const {
  float len = getLength();
  if (len > 0) return Vec3(x_comp / len, y_comp / len, z_comp / len);
  return Vec3();
}

float Vec3::dotProduct(const Vec3& other) const {
  return x_comp * other.x_comp + y_comp * other.y_comp + z_comp * other.z_comp;
}

Vec3 Vec3::crossProduct(const Vec3& other) const {
  return Vec3(y_comp * other.z_comp - z_comp * other.y_comp,
              z_comp * other.x_comp - x_comp * other.z_comp,
              x_comp * other.y_comp - y_comp * other.x_comp);
}

Vec3 Vec3::operator+(const Vec3& other) const {
  return Vec3(x_comp + other.x_comp, y_comp + other.y_comp,
              z_comp + other.z_comp);
}

Vec3 Vec3::operator-(const Vec3& other) const {
  return Vec3(x_comp - other.x_comp, y_comp - other.y_comp,
              z_comp - other.z_comp);
}

float Vec3::operator*(const Vec3& other) const { return dotProduct(other); }

std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
  os << "(" << vec.x_comp << ", " << vec.y_comp << ", " << vec.z_comp << ")";
  return os;
}
