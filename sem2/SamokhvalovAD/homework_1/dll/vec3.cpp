#include "vec3.h"

Vec3 Vec3::sum(Vec3 other) {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::minus(Vec3 other) {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::scalarV(Vec3 other) {
  return Vec3(x * other.x, y * other.y, z * other.z);
}

Vec3 Vec3::scalar(double scalar) {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::vec(Vec3 other) {
  return Vec3(y * other.z - z * other.y, z * other.x - x * other.z,
              x * other.y - y * other.x);
}

Vec3 Vec3::norm() {
  float length = this->length();
  if (length == 0) {
    return Vec3(0, 0, 0);
  }
  return Vec3(x / length, y / length, z / length);
}