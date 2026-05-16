#include "vec3.h"

#include <cmath>

namespace math {

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}

Vec3::Vec3(double x_value, double y_value, double z_value)
    : x(x_value), y(y_value), z(z_value) {}

double Vec3::Length() const { return std::sqrt(x * x + y * y + z * z); }

Vec3 Vec3::Normalized() const {
  double len = Length();
  if (len == 0.0) {
    return *this;
  }
  return Vec3(x / len, y / len, z / len);
}

Vec3 operator+(const Vec3& a, const Vec3& b) {
  return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
  return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator*(const Vec3& v, double scalar) {
  return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

Vec3 operator*(double scalar, const Vec3& v) { return v * scalar; }

double Dot(const Vec3& a, const Vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Cross(const Vec3& a, const Vec3& b) {
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

std::ostream& operator<<(std::ostream& out, const Vec3& v) {
  out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return out;
}

}  // namespace math
