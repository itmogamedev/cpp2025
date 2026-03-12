#pragma once

#include <iostream>

#ifdef VECTLIB_EXPORTS
#define VECTLIB_API __declspec(dllexport)
#else
#define VECTLIB_API __declspec(dllimport)
#endif

extern "C" VECTLIB_API struct Vec3 {
	double x = 0;
	double y = 0;
	double z = 0;

	Vec3(double xVal = 0, double yVal = 0, double zVal = 0);

	Vec3 operator+(const Vec3& a) const;
	Vec3 operator-(const Vec3& a) const;
	double operator*(const Vec3& a) const;
	Vec3 operator*(double a) const;
};

extern "C" VECTLIB_API std::ostream& operator<<(std::ostream& os, const Vec3& v);

extern "C" VECTLIB_API Vec3 vecSum(Vec3 a, Vec3 b);
extern "C" VECTLIB_API Vec3 vecSubtraction(Vec3 a, Vec3 b);
extern "C" VECTLIB_API double scalMult(Vec3 a, Vec3 b);
extern "C" VECTLIB_API Vec3 vecMult(Vec3 a, Vec3 b);
extern "C" VECTLIB_API double lenVec(Vec3 a);
extern "C" VECTLIB_API Vec3 normVec(Vec3 a);

VECTLIB_API Vec3 vecScalMult(Vec3 a, double b);
VECTLIB_API Vec3 vecScalMult(double b, Vec3 a);