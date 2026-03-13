#include "pch.h"

#include "vec3.h"

#include <cmath>


Vec3 sum(const Vec3& l_vec, const Vec3& r_vec) {
  return Vec3(l_vec.x + r_vec.x, l_vec.y + r_vec.y, l_vec.z + r_vec.z);
}

Vec3 minus(const Vec3& l_vec, const Vec3& r_vec) {
  return Vec3(l_vec.x - r_vec.x, l_vec.y - r_vec.y, l_vec.z - r_vec.z);
}

Vec3 multiplic_by_sc(int sc, const Vec3& vec) {
  return Vec3(sc * vec.x, sc * vec.y, sc * vec.z);
}

double dot_prod(const Vec3& l_vec, const Vec3& r_vec) {
  return l_vec.x * r_vec.x + l_vec.y * r_vec.y + l_vec.z * r_vec.z;
}

Vec3 vector_product(const Vec3& l_vec, const Vec3& r_vec) {
  double x = l_vec.y * r_vec.z - l_vec.z * r_vec.y;
  double y = l_vec.z * r_vec.x - l_vec.x * r_vec.z;
  double z = l_vec.x * r_vec.y - l_vec.y * r_vec.x;

  return Vec3(x, y, z);
}

double length(const Vec3& vec) {
  return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

Vec3 norm(const Vec3& vec) {
  if (vec.x == 0 && vec.y == 0 && vec.z == 0) {
    return vec;
  }

  double l = length(vec);

  Vec3 new_vec;

  new_vec.x = vec.x / l;
  new_vec.y = vec.y / l;
  new_vec.z = vec.z / l;

  return new_vec;
}

Vec3 operator+(const Vec3& l_vec, const Vec3& r_vec) {
  return sum(l_vec, r_vec);
}

Vec3 operator-(const Vec3& l_vec, const Vec3& r_vec) {
  return minus(l_vec, r_vec);
}

Vec3 operator*(const Vec3& vec, int sc) { return multiplic_by_sc(sc, vec); }
