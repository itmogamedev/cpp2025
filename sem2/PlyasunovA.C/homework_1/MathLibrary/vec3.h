#ifndef MATHLIBRARY_VEC3_H_
#define MATHLIBRARY_VEC3_H_

#include <iostream>

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

namespace math {

	struct MATHLIBRARY_API Vec3 {
		double x;
		double y;
		double z;

		Vec3();
		explicit Vec3(double x_val, double y_val, double z_val);
		Vec3(const Vec3& other);

		Vec3& operator=(const Vec3& other);
	};

	MATHLIBRARY_API Vec3 add(const Vec3& a, const Vec3& b);
	MATHLIBRARY_API Vec3 subtract(const Vec3& a, const Vec3& b);
	MATHLIBRARY_API Vec3 multiply(const Vec3& v, double scalar);
	MATHLIBRARY_API double dot(const Vec3& a, const Vec3& b);
	MATHLIBRARY_API Vec3 cross(const Vec3& a, const Vec3& b);
	MATHLIBRARY_API double length(const Vec3& v);
	MATHLIBRARY_API Vec3 normalize(const Vec3& v);

	MATHLIBRARY_API Vec3 operator+(const Vec3& a, const Vec3& b);
	MATHLIBRARY_API Vec3 operator-(const Vec3& a, const Vec3& b);
	MATHLIBRARY_API Vec3 operator*(const Vec3& v, double scalar);
	MATHLIBRARY_API Vec3 operator*(double scalar, const Vec3& v);
	MATHLIBRARY_API std::ostream& operator<<(std::ostream& os, const Vec3& v);

}

#endif