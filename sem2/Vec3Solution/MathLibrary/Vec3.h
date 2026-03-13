#pragma once

// Макрос для экспорта/импорта функций
#ifdef MATHLIBRARY_EXPORTS
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllimport)
#endif

#include <iostream>

struct MATH_API Vec3 {
    double x, y, z;

    Vec3(double x = 0, double y = 0, double z = 0);

    Vec3 multiply(double scalar) const;      
    double dot(const Vec3& other) const;     
    Vec3 cross(const Vec3& other) const;    
    double length() const;                   
    Vec3 normalize() const;                  

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    double operator*(const Vec3& other) const; 
};

MATH_API std::ostream& operator<<(std::ostream& os, const Vec3& v);
