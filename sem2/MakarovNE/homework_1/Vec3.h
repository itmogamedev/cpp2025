#pragma once

#ifdef MATHVEC3_EXPORTS
#define MATHVEC3_API __declspec(dllexport)
#else
#define MATHVEC3_API __declspec(dllimport)
#endif

#include <iostream>

struct MATHVEC3_API Vec3
{
	float x_coord;
	float y_coord;
	float z_coord;

	Vec3();
	Vec3(float x, float y, float z);

	Vec3 operator+(const Vec3& other) const;
	Vec3 operator-(const Vec3& other) const;
	Vec3 operator*(float scalar) const;
	friend MATHVEC3_API Vec3 operator*(float scalar, const Vec3& vec);

	float skProduct(const Vec3& other) const;
	Vec3 vcProduct(const Vec3& other) const;
	float length() const;
	Vec3 normalize() const;
};

MATHVEC3_API std::ostream&
operator<<(std::ostream& os, const Vec3& vec);