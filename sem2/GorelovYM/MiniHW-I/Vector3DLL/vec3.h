#pragma once
#include <cmath>
#include <iostream>
#include <string>

// для создания и dll и lib
#ifdef VECTOR3DLL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

// СТРУКТУРА СТРАУС-ТРУПА
struct DECLSPEC Vec3 {
  // приватные переменные
 private:
  float x, y, z;

 public:
  // конструктор
  Vec3(float cx = 0, float cy = 0, float cz = 0) : x(cx), y(cy), z(cz) {}

  // геттеры и сеттеры
  float getX() { return x; }
  float getY() { return y; }
  float getZ() { return z; }
  void setX(float cx) { x = cx; }
  void setY(float cy) { x = cy; }
  void setZ(float cz) { x = cz; }

  // сложение векторов
  Vec3 add(const Vec3 right) const {
    return Vec3(x + right.x, y + right.y, z + right.z);
  }

  // вычитание векторов
  Vec3 sub(const Vec3 right) const {
    return Vec3(x - right.x, y - right.y, z - right.z);
  }

  // скалярное умножение
  Vec3 scale(float scale) const {
    return Vec3(scale * x, scale * y, scale * z);
  }

  // скалярное произведение
  float scalar(Vec3 right) const {
    return x * right.x + y * right.y + z * right.z;
  }

  // векторное произведение
  Vec3 vector(Vec3 right) const {
    return Vec3(y * right.z - z * right.y, x * right.z - z * right.x,
                x * right.y - y * right.x);
  }

  // длинна вектора
  float length() const { return std::sqrt(x * x + y * y + z * z); }

  // нормализация вектора
  Vec3 normalized() const {
    return Vec3(x / length(), y / length(), z / length());
  }

  // оверрайды операторов
  Vec3 operator+(const Vec3 right) const { return add(right); }
  Vec3 operator-(const Vec3 right) const { return sub(right); }
  Vec3 operator*(float right) const { return scale(right); }
  friend Vec3 operator*(float s, const Vec3 v) { return v.scale(s); }
  float operator*(const Vec3 right) const { return scalar(right); }

  // оверрайд вывода в консоль
  friend std::ostream& operator<<(std::ostream& stream, const Vec3& vec) {
    return stream << "(" << std::to_string(vec.x) << ", "
                  << std::to_string(vec.y) << ", " << std::to_string(vec.z)
                  << ")";
  }
};
