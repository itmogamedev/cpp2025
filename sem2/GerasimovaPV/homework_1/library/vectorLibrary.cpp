//
// Created by Admin on 08.03.2026.
//
#include "vectorLibrary.h"

#include <cmath>


Vec3 operator+(const Vec3& a, const Vec3& b)
{
  Vec3 result;
  result.x = a.x + b.x;
  result.y = a.y + b.y;
  result.z = a.z + b.z;
  return result;
}

Vec3 operator-(const Vec3& a, const Vec3& b)
{
  Vec3 result;
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  result.z = a.z - b.z;
  return result;
}

Vec3 operator*(const Vec3& a, float scalar)
{
  Vec3 result;
  result.x = a.x * scalar;
  result.y = a.y * scalar;
  result.z = a.z * scalar;
  return result;
}

float dot(const Vec3& a, const Vec3& b)
{
  float result = a.x * b.x + a.y * b.y + a.z * b.z;
  return result;
}

Vec3 cross(const Vec3& a, const Vec3& b)
{
  Vec3 result;
  result.x = a.y * b.z - a.z * b.y;
  result.y = a.z * b.x - a.x * b.z;
  result.z = a.x * b.y - a.y * b.x;
  return result;
}

float length(const Vec3& v)
{
  float result = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  return result;
}

Vec3 norm(const Vec3& v)
{
  Vec3 result;
  float len = length(v);
  if (len == 0) return Vec3{0,0,0};
  result.x = v.x / len;
  result.y = v.y / len;
  result.z = v.z / len;
  return result;
}

std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}
