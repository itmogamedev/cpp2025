#include "pch.h" 

#include <cmath>

#include "MathLibrary.h"

vector vector::operator+(const vector& other) const {
  return vector(x + other.x, y + other.y, z + other.z);
}

vector vector::operator-(const vector& other) const {
  return vector(x - other.x, y - other.y, z - other.z);
}

vector vector::operator*(const double scalar) const {
  return vector(x * scalar, y * scalar, z * scalar);
}

vector add(vector& a, vector& b) { return a + b; }

vector substract(vector& a, vector& b) { return a - b; }

vector scalar(vector& a, double scalar) { return a * scalar; }

double scalarMultiply(vector& a, vector& b) { 
    return a.x * b.x + a.y * b.y + a.z * b.z; 
}

vector vectorMultiply(vector& a, vector& b) { 
    return vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); 
}

double length(vector& a) {
    return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z); 
}

vector normalize(vector& a) { 
  double vecLen = length(a);
  return vector(a.x / vecLen, a.y / vecLen, a.z / vecLen);
}