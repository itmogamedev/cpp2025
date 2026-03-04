#ifndef __VEC3_H
#define __VEC3_H

#include <cmath>
#include <iostream>

class Vec3 {
 public:
  float x;
  float y;
  float z;

  Vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  Vec3 operator+(const Vec3 &o) const {
    return Vec3(this->x + o.x, this->y + o.y, this->z + o.z);
  }

  Vec3 operator-() const { return Vec3(-this->x, -this->y, -this->z); }

  Vec3 operator-(const Vec3 &o) const { return *this + (-o); }

  Vec3 operator+=(const Vec3 &o) {
    *this = *this + o;
    return *this;
  }

  Vec3 operator-=(const Vec3 &o) {
    *this = *this - o;
    return *this;
  }

  Vec3 operator*(float o) const {
    return Vec3(this->x * o, this->y * o, this->z * o);
  }

  Vec3 operator*=(float o) {
    *this = *this * o;
    return *this;
  }

  Vec3 operator/(float o) const {
    return Vec3(this->x / o, this->y / o, this->z / o);
  }

  Vec3 operator/=(float o) {
    *this = *this / o;
    return *this;
  }

  float dot(const Vec3 &o) const {
    return this->x * o.x + this->y * o.y + this->z * o.z;
  }

  float operator*(const Vec3 &o) const { return this->dot(o); }

  Vec3 cross(const Vec3 &o) const {
    /*
            x		y		z
            t.x		t.y		t.z
            o.x		o.y		o.z
    */

    return Vec3((this->y * o.z) - (this->z * o.y),
                -1 * (this->x * o.z) - (this->z * o.x),
                (this->x * o.y) - (this->y * o.x));
  }

  float len() const { return std::sqrt(*this * *this); }

  Vec3 norm() const { return *this / this->len(); }
};

std::ostream &operator<<(std::ostream &os, const Vec3 &o) {
  os << o.x << " " << o.y << " " << o.z;
  return os;
}

#endif