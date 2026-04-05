// Приведенный ниже блок ifdef — это стандартный метод создания макросов,
// упрощающий процедуру экспорта из библиотек DLL. Все файлы данной DLL
// скомпилированы с использованием символа DLL1_EXPORTS Символ, определенный в
// командной строке. Этот символ не должен быть определен в каком-либо проекте,
// использующем данную DLL. Благодаря этому любой другой проект, исходные файлы
// которого включают данный файл, видит функции DLL1_API как импортированные из
// DLL, тогда как данная DLL видит символы, определяемые данным макросом, как
// экспортированные.
#pragma once

#include <cmath>
#include <iostream>
#include <string>

#ifdef DLL1_EXPORTS
#define DLL1_API __declspec(dllexport)
#else
#define DLL1_API __declspec(dllimport)
#endif

//// Этот класс экспортирован из библиотеки DLL
// class DLL1_API CDll1 {
// public:
//	CDll1(void);
//	// TODO: добавьте сюда свои методы.
// };
//
// extern DLL1_API int nDll1;
//
// DLL1_API int fnDll1(void);
//

struct DLL1_API Vec3 {
  // Переменные - координаты
  float x_coord, y_coord, z_coord;

 public:
  // Конструктор. По умолчанию создаётся единичный вектор
  Vec3(float x = 1, float y = 1, float z = 1) {
    x_coord = x;
    y_coord = y;
    z_coord = z;
  }

  // Геттеры
  float getX() const { return x_coord; }
  float getY() const { return y_coord; }
  float getZ() const { return z_coord; }
  // Сеттеры
  void setX(float X) { x_coord = X; }
  void setY(float Y) { y_coord = Y; }
  void setZ(float Z) { z_coord = Z; }

  // Функции:
  //  Сложение векторов
  Vec3 add(const Vec3& vec) const {
    return Vec3{x_coord + vec.x_coord, y_coord + vec.y_coord,
                z_coord + vec.z_coord};
  }

  // Вычитание векторов
  Vec3 subtr(const Vec3& vec) const {
    return Vec3{x_coord - vec.x_coord, y_coord - vec.y_coord,
                z_coord - vec.z_coord};
  }

  // Умножение вектора на скаляр
  Vec3 scalMult(const float& scal) const {
    return Vec3{x_coord * scal, y_coord * scal, z_coord * scal};
  }

  // Скалярное произведение
  float scalProd(const Vec3& vec) const {
    return x_coord * vec.x_coord + y_coord * vec.y_coord +
           z_coord * vec.z_coord;
  }

  // Векторное произведение
  Vec3 vectProd(const Vec3& vec) const {
    return Vec3{y_coord * vec.z_coord - z_coord * vec.y_coord,
                z_coord * vec.x_coord - x_coord * vec.z_coord,
                x_coord * vec.y_coord - y_coord * vec.x_coord};
  }

  // Вычисление длины вектора
  float len() const {
    return std::sqrt(x_coord * x_coord + y_coord * y_coord + z_coord * z_coord);
  }

  // Нормализация
  Vec3 norm() const {
    return Vec3{x_coord / len(), y_coord / len(), z_coord / len()};
  }

  // Переопределение операторов:
  Vec3 operator+(const Vec3& vec) const {
    return Vec3{x_coord + vec.x_coord, y_coord + vec.y_coord,
                z_coord + vec.z_coord};
  }
  Vec3 operator-(const Vec3& vec) const {
    return Vec3{x_coord - vec.x_coord, y_coord - vec.y_coord,
                z_coord - vec.z_coord};
  }
  Vec3 operator*(const float& scal) const {
    return Vec3{x_coord * scal, y_coord * scal, z_coord * scal};
  }
  float operator*(const Vec3& vec) const {
    return x_coord * vec.x_coord + y_coord * vec.y_coord +
           z_coord * vec.z_coord;
  }
  friend std::ostream& operator<<(std::ostream& stream, const Vec3& vec) {
    stream << vec.getX() << " " << vec.getY() << " " << vec.getZ();
    return stream;
  }
};
