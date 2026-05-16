#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>

struct MATHLIBRARY_API vector {
  double x;
  double y;
  double z;

  vector(double xx = 0, double yy = 0, double zz = 0) : x(xx), y(yy), z(zz) {}

  vector operator+(const vector& other) const;
  vector operator-(const vector& other) const;
  vector operator*(const double scalar) const;
  friend std::ostream& operator<<(std::ostream& os, const vector& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
  }

  };

MATHLIBRARY_API vector add(vector& a, vector& b);
MATHLIBRARY_API vector substract(vector& a, vector& b);
MATHLIBRARY_API vector scalar(vector& a, double scalar);
MATHLIBRARY_API double scalarMultiply(vector& a, vector& b);
MATHLIBRARY_API vector vectorMultiply(vector& a, vector& b);
MATHLIBRARY_API double length(vector& a);
MATHLIBRARY_API vector normalize(vector& a);
  