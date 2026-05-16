
#include "pch.h"
#include "Vec3.h"

Vec3::Vec3(double x, double y, double z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

Vec3 Vec3::operator+(Vec3& other) const {
  return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vec3 Vec3::operator-(Vec3& other) const {
  return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vec3 Vec3::operator*(Vec3& other) const {
  return Vec3(this->x * other.x, this->y * other.y, this->z * other.z);
}

Vec3 Vec3::operator*(double scale) const {
  return Vec3(x * scale, y * scale, z * scale);
}

Vec3 Vec3::operator/(double scale) const {
  return Vec3(x / scale, y / scale, z / scale);
}

double Vec3::getLenght() const { return sqrt(x * x + y * y + z * z); }

void Vec3::normalize() {
  double norm = getLenght();
  if (!norm) {
    return;
  }
  x = x / norm;
  y = y / norm;
  z = z / norm;
}

Vec3 cross(const Vec3& first, const Vec3 second) {
  return Vec3(first.y * second.z - first.z * second.y,
              first.z * second.x - first.x * second.z,
              first.x * second.y - first.y * second.x);
}
