#include "pch.h"

Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3 Vec3::Summator(const Vec3& another_vec) const {
  return Vec3(x + another_vec.x, y + another_vec.y, z + another_vec.z);
}

Vec3 Vec3::Minusator(const Vec3& another_vec) const {
  return Vec3(x - another_vec.x, y - another_vec.y, z - another_vec.z);
}

Vec3 Vec3::umnojatorConst(double constanta) const {
  return Vec3(x * constanta, y * constanta, z * constanta);
}

double Vec3::Scalyarnoe(const Vec3& another_vec) const {
  return x * another_vec.x + y * another_vec.y + z * another_vec.z;
}

Vec3 Vec3::Vectornoe(const Vec3& another_vec) const {
  return Vec3(y * another_vec.z - z * another_vec.y,
              z * another_vec.x - x * another_vec.z,
              x * another_vec.y - y * another_vec.x);
}

double Vec3::length() const { return std::sqrt(x * x + y * y + z * z); }

Vec3 Vec3::normalizedVersion() const {
  double len = length();
  if (len > 0) {
    return Vec3(x / len, y / len, z / len);
  }
  return Vec3(0, 0, 0);
}

Vec3 constUmnojator(double constanta, const Vec3& vec) {
  return Vec3(constanta * vec.getX(), constanta * vec.getY(),
              constanta * vec.getZ());
}

std::ostream& funcForOut(std::ostream& os, const Vec3& vec) {
  os << "(" << vec.getX() << ", " << vec.getY() << ", " << vec.getZ() << ")";
  return os;
}
