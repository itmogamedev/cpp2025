#pragma once
#include <iostream>
#include <cmath> 
#ifdef HW1_EXPORTS
#define HW1_API __declspec(dllexport)
#else
#define HW1_API __declspec(dllimport)
#endif

struct HW1_API Vec3 {
public:
    Vec3(double v1, double v2, double v3);
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(double value) const;
    double dotProduct(const Vec3& other) const;
    Vec3 crossProduct(const Vec3& other) const;
    double len() const;
    Vec3 getUnit() const;
    friend HW1_API std::ostream& operator<<(std::ostream& os, const Vec3& obj);
private:
    double v[3];
};