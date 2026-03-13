#pragma once
#include <iostream>

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

struct MATHLIBRARY_API Vec3 {
    double x_coord;
    double y_coord;
    double z_coord;
    Vec3();
    Vec3(double x, double y, double z);
    Vec3(const Vec3& other); 
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(double scalar) const;
    friend MATHLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);
    friend MATHLIBRARY_API Vec3 operator*(double scalar, const Vec3& vec);
};

MATHLIBRARY_API Vec3 addVectors(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 subtractVectors(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 multiplyByScalar(const Vec3& vec, double scalar);
MATHLIBRARY_API double dotProduct(const Vec3& a, const Vec3& b);
MATHLIBRARY_API Vec3 crossProduct(const Vec3& a, const Vec3& b);
MATHLIBRARY_API double vectorLength(const Vec3& vec);
MATHLIBRARY_API Vec3 normalizeVector(const Vec3& vec);