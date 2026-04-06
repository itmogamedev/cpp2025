#pragma once

#include <iostream>

struct Vec3 {
  double x;
  double y;
  double z;

  Vec3();
  Vec3(double x_value, double y_value, double z_value);

  double length() const;
  Vec3 normalize() const;
};

Vec3 operator+(const Vec3& left, const Vec3& right);
Vec3 operator-(const Vec3& left, const Vec3& right);
Vec3 operator*(const Vec3& vector, double scalar);

std::ostream& operator<<(std::ostream& out, const Vec3& vector);

double dotProduct(const Vec3& left, const Vec3& right);
Vec3 crossProduct(const Vec3& left, const Vec3& right);
Vec3 crossProduct(const Vec3& left, const Vec3& right);
