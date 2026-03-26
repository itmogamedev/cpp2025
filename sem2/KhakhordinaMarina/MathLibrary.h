#pragma once

#ifdef MATHLIB_EXPORTS
#define MATHLIB_API __declspec(dllexport)
#else
#define MATHLIB_API __declspec(dllimport)
#endif

#include <iostream>
#include <cmath>

struct MATHLIB_API Vec {
  float x, y, z;
  
  Vec(float x = 0, float y = 0, float z = 0);

	// operators 
  Vec operator+(const Vec& other) const;
  Vec operator-(const Vec& other) const;
  Vec operator*(float scalar) const; // na number
  float operator*(const Vec& other) const; // scalar

	//metods 
  float length() const;
  Vec normalize() const;
  Vec cross(const Vec& other) const; //vectr proiz

  friend MATHLIB_API std::ostream& operator<<(std::ostream& os, const Vec& v);
};