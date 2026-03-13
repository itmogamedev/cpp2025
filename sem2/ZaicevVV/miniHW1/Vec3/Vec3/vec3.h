#pragma once

#ifdef VEC3_EXPORTS
#define VEC3_API __declspec(dllexport)
#else
#define VEC3_API __declspec(dllimport)
#endif

#include <iostream>

struct Vec3 {
  double x, y, z;
  Vec3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

VEC3_API Vec3 sum(const Vec3& l_vec, const Vec3& r_vec);
VEC3_API Vec3 minus(const Vec3& l_vec, const Vec3& r_vec);
VEC3_API Vec3 multiplic_by_sc(int sc, const Vec3& vec);
VEC3_API double dot_prod(const Vec3& l_vec, const Vec3& r_vec);
VEC3_API Vec3 vector_product(const Vec3& l_vec, const Vec3& r_vec);
VEC3_API double length(const Vec3& vec);
VEC3_API Vec3 norm(const Vec3& vec);

VEC3_API Vec3 operator+(const Vec3& l_vec, const Vec3& r_vec);
VEC3_API Vec3 operator-(const Vec3& l_vec, const Vec3& r_vec);
VEC3_API Vec3 operator*(const Vec3& vec, int sc);
inline std::ostream& operator<<(std::ostream& stream, const Vec3& vec) {
	stream << vec.x << ' ' << vec.y << ' ' << vec.z;
	return stream;
}
