#include "pch.h"
// По какой то причине "pch.h" пытается уйти вниз, под "MathLibrary.h".
// Только эта вставка, почемуто, предотвращает сдвиг
#include <cmath>

#include "MathLibrary.h"
void Add(const int* a, const int* b, float* res) {
  for (int i = 0; i < 3; i++) res[i] = a[i] + b[i];
}
void Subtract(const int* a, const int* b, float* res) {
  for (int i = 0; i < 3; i++) res[i] = a[i] - b[i];
}
void Multiply(const int* a, float scalar, float* res) {
  for (int i = 0; i < 3; i++) res[i] = a[i] * scalar;
}
float Dot(const int* a, const int* b) {
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
void Cross(const int* a, const int* b, float* res) {
  res[0] = a[1] * b[2] - a[2] * b[1];
  res[1] = a[2] * b[0] - a[0] * b[2];
  res[2] = a[0] * b[1] - a[1] * b[0];
}
float GetLength(const int* a) {
  return std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}
void Normalize(const int* a, float* res) {
  float len = GetLength(a);
  if (len > 0) {
    float invLen = 1 / len;
    for (int i = 0; i < 3; i++) res[i] = a[i] * invLen;
  }
}
