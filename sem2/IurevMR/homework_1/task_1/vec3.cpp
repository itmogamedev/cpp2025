#include "vec3.h"

#include <iostream>
#include <ostream>
#include <cmath>

void add(Vec3 *a, const Vec3 *b) {
  a->x += b->x;
  a->y += b->y;
  a->z += b->z;
}

void mul(Vec3 *a, float b) {
  a->x *= b;
  a->y *= b;
  a->z *= b;
}

void cross(Vec3 *c, const Vec3 *a, const Vec3 *b) {
  *c = (Vec3) {
    .x = a->y * b->z - b->y * a->z,
    .y = a->x * b->z - b->x * a->z,
    .z = a->x * b->y - b->x * a->y
  };
}

void normalize(Vec3 *a) {
  float l = a->x * a->x + a->y * a->y + a->z * a->z;
  if(l < EPSILON) {
    *a = (Vec3){0};
  } else {
    l = sqrt(l);
    a->x /= l;
    a->y /= l;
    a->z /= l;
  }
}

float dot(const Vec3 *a, const Vec3 *b) {
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

float len(const Vec3 *a) {
  return sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
}

Vec3 operator+(Vec3 &left, Vec3 &right) {
    return (Vec3) {
        .x = left.x + right.x,
        .y = left.y + right.y,
        .z = left.z + right.z
    };
}

Vec3 operator-(Vec3 &left, Vec3 &right) {
  return (Vec3) {
    .x = left.x - right.x,
    .y = left.y - right.y,
    .z = left.z - right.z
  };
}

float operator*(Vec3 &left, Vec3 &right) {
  return left.x * right.x + left.y * right.y + left.z + right.z;
}

std::ostream& operator<<(std::ostream& os, Vec3& vec) {
  os << "{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
  return os;
}
