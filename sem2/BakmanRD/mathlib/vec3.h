#pragma once
#include <iostream>

#define MATHLIB

struct MATHLIB Vec3 {
 double x, y, z;

 // Конструктор с параметрами по умолчанию
 Vec3(double x = 0.0, double y = 0.0, double z = 0.0);
};

// Операторы
MATHLIB Vec3 operator+(const Vec3& a, const Vec3& b);
MATHLIB Vec3 operator-(const Vec3& a, const Vec3& b);
MATHLIB Vec3 operator*(const Vec3& v, double scalar);
MATHLIB std::ostream& operator<<(std::ostream& os, const Vec3& v);

inline Vec3 operator*(double scalar, const Vec3& v) { return v * scalar; }

MATHLIB double dot(const Vec3& a, const Vec3& b);
MATHLIB Vec3 cross(const Vec3& a, const Vec3& b);
MATHLIB double length(const Vec3& v);
MATHLIB Vec3 normalize(const Vec3& v);