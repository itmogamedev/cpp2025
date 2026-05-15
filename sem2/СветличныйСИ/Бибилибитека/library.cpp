#include "library.h"

#include <cmath>


Vec3 Vec3::operator+(const Vec3 &other) const
{
  return {x + other.x, y + other.y, z + other.z};
}

Vec3 Vec3::operator-(const Vec3 &other) const
{
  return Vec3(x - other.x, y - other.y, z - other.z);
}

double Vec3::operator*(const Vec3 &other) const
{
  return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::operator*(double a) const
{
  return Vec3(x * a, y * a, z * a);
}

Vec3 Vec3::operator^(Vec3 other) const
{
  return Vec3(y * other.z - other.y * z,
            z * other.x - other.z * x,
            x * other.y - other.x * y);
}

std::ostream &operator<<(std::ostream &os, const Vec3 &p)
{
  os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
  return os;
}

double Vec3::length()
{
  return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalize()
{
  double l = length();
  if (l == 0.0)
    return Vec3(0, 0, 0);
  else
    return Vec3(x / l, y / l, z / l);
}
