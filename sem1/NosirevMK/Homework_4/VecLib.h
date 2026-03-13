#pragma once

#include <iostream>
#include <cmath>

// Макрос для экспорта/импорта функций и классов из DLL
#ifdef VECLIB_EXPORTS
#define VECLIB_API __declspec(dllexport)
#else
#define VECLIB_API __declspec(dllimport)
#endif

struct VECLIB_API Vec3
{
    float x, y, z;

    // Конструкторы
    Vec3();
    Vec3(float x, float y, float z);

    // Методы
    float Length() const;
    Vec3 Normalize() const;

    // Перегрузка операторов (члены класса)
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(float scalar) const;

    // Дружественные функции для скалярного умножения (scalar * vec) и вывода
    friend VECLIB_API Vec3 operator*(float scalar, const Vec3& vec);
    friend VECLIB_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);
};

// Отдельные функции для скалярного и векторного произведения
VECLIB_API float DotProduct(const Vec3& a, const Vec3& b);
VECLIB_API Vec3 CrossProduct(const Vec3& a, const Vec3& b);
