#pragma once

#ifdef VEC3_EXPORTS
#define VEC3_API __declspec(dllexport)
#else
#define VEC3_API __declspec(dllimport)
#endif

#include <iostream>

struct VEC3_API Vec3 {
private:
	double x, y, z;

public:
	Vec3();
	Vec3(double, double, double);

	double getX() const;
	double getY() const;
	double getZ() const;
	Vec3 getNormalized() const;
	double getLength() const;

	Vec3 operator+(const Vec3&) const;
	Vec3 operator-(const Vec3&) const;

	Vec3 operator*(const double&) const;
	double operator*(const Vec3&) const; // scalar vec mult
	Vec3 operator%(const Vec3&) const; // vec mult
	
};

VEC3_API Vec3 operator*(const double&, const Vec3&);

VEC3_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);