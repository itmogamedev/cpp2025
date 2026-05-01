#pragma once
#ifdef DLL1_EXPORTS
#define DLL1_API __declspec(dllexport)
#else
#define DLL1_API __declspec(dllimport)
#endif

#include <iostream>

struct DLL1_API Vec3 {
	double x, y, z;

	Vec3(double x = 0, double y = 0, double z = 0);

	Vec3 operator+(const Vec3& other) const;
	Vec3 operator-(const Vec3& other) const;
	Vec3 operator*(double scalar) const;
};
DLL1_API Vec3 operator*(double scalar, const Vec3& vector);
DLL1_API std::ostream& operator<<(std::ostream& os, const Vec3& vector);

DLL1_API Vec3 add(const Vec3& a, const Vec3& b);
DLL1_API Vec3 subtract(const Vec3& a, const Vec3& b);
DLL1_API Vec3 multiply(const Vec3& v, double scalar);
DLL1_API double multiplyScalar(const Vec3& a, const Vec3& b);
DLL1_API Vec3 multiplyVector(const Vec3& a, const Vec3& b);
DLL1_API double length(const Vec3& v);
DLL1_API Vec3 normalize(const Vec3& v);