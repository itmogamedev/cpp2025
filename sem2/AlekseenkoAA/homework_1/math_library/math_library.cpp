#include "pch.h"
#include "math_library.h"

Vec3 addVec3(const Vec3& vec_1, const Vec3& vec_2) {
  return Vec3(vec_1.x + vec_2.x, vec_1.y + vec_2.y, vec_1.z + vec_2.z);
}

Vec3 subVec3(const Vec3& vec_1, const Vec3& vec_2) {
  return Vec3(vec_1.x - vec_2.x, vec_1.y - vec_2.y, vec_1.z - vec_2.z);
}

Vec3 mulVec3(long double x, const Vec3& vec) {
  return Vec3(vec.x * x, vec.y * x, vec.z * x);
}

Vec3 divVec3(long double x, const Vec3& vec) {
  return Vec3(vec.x / x, vec.y / x, vec.z / x);
}

long double dotVec3(const Vec3& vec_1, const Vec3& vec_2) {
  return (vec_1.x * vec_2.x + vec_1.y * vec_2.y + vec_1.z * vec_2.z);
}

Vec3 crossVec3(const Vec3& vec_1, const Vec3& vec_2) {
  return Vec3(detMat3x3Separated(Matrix3x3(unit_vector, vec_1, vec_2)));
}

Vec3 normVec3(const Vec3& vec) {
  return (vec / lenghtVec3(vec));
}  // знаю, что делить на 0 нельзя...

long double lenghtVec3(const Vec3& vec) {
  return std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2) +
                   std::pow(vec.z, 2));
}

Vec3 operator-(const Vec3& vec, const Vec3& vec_other) {
  return subVec3(vec, vec_other);
}

Vec3 operator+(const Vec3& vec, const Vec3& vec_other) {
  return addVec3(vec, vec_other);
}

Vec3 operator*(const Vec3& vec, long double x) { return mulVec3(x, vec); }

Vec3 operator*(long double x, const Vec3& vec) { return mulVec3(x, vec); }

Vec3 operator/(const Vec3& vec, long double x) { return divVec3(x, vec); }

Vec3 operator^(const Vec3& vec, const Vec3& vec_other) {
  return crossVec3(vec, vec_other);
}

std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
  return os << "\nИнформация о конечном векторе: \n"
            << "Координаты: \n"
            << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z
            << "\nРазмер в памяти: " << sizeof(vec)
            << "\n";  // интересно, что компилятор на windows msvc дает меньше
                      // точности long double, чем gcc++ (там вектор занимает
                      // памяти 48 бит, вместо 24 на msvc)
}

long double detMat2x2(const Matrix2x2& matrix) {
  return (matrix.mat[0] * matrix.mat[3]) - (matrix.mat[2] * matrix.mat[1]);
}

// не используется, но оставил как базу на будущее :) ...
long double detMat3x3(const Matrix3x3& matrix) {
  long double x = detMat2x2(Matrix2x2(matrix.mat[4], matrix.mat[5],
                                      matrix.mat[7], matrix.mat[8]));  // x
  long double y = -detMat2x2(Matrix2x2(matrix.mat[3], matrix.mat[5],
                                       matrix.mat[6], matrix.mat[8]));  // y
  long double z = detMat2x2(Matrix2x2(matrix.mat[3], matrix.mat[4],
                                      matrix.mat[6], matrix.mat[7]));  // z
  return (matrix.mat[0] * x) + (matrix.mat[1] * y) + (matrix.mat[2] * z);
}

Vec3 detMat3x3Separated(const Matrix3x3& matrix) {
  long double x = detMat2x2(Matrix2x2(matrix.mat[4], matrix.mat[5],
                                      matrix.mat[7], matrix.mat[8]));  // x
  long double y = -detMat2x2(Matrix2x2(matrix.mat[3], matrix.mat[5],
                                       matrix.mat[6], matrix.mat[8]));  // y
  long double z = detMat2x2(Matrix2x2(matrix.mat[3], matrix.mat[4],
                                      matrix.mat[6], matrix.mat[7]));  // z
  return Vec3(x, y, z);
}
