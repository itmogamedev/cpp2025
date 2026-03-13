#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>

class MATHLIBRARY_API Vec3 {
private:
	double x, y, z;

public:
	static const Vec3 Zero;

	// Constructors
	Vec3();
	Vec3(double x, double y, double z);
	Vec3(const Vec3& other);

	// Getters
	double getX() const;
	double getY() const;
	double getZ() const;

	// Setters
	void setX(double x);
	void setY(double y);
	void setZ(double z);

	// Arithmetic operations
	Vec3 operator+(const Vec3& other) const;
	Vec3 operator-(const Vec3& other) const;
	Vec3 operator*(double scalar) const;

	// Friend function for scalar multiplication (scalar * vector)
	friend MATHLIBRARY_API Vec3 operator*(double scalar, const Vec3& vec);

	// Compound assignment
	Vec3& operator+=(const Vec3& other);
	Vec3& operator-=(const Vec3& other);
	Vec3& operator*=(double scalar);

	// Dot product
	double dot(const Vec3& other) const;

	// Cross product
	Vec3 cross(const Vec3& other) const;

	// Vector length
	double length() const;

	// Normalization
	Vec3 normalize() const;

	// Friend function for output
	friend MATHLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& vec);
};